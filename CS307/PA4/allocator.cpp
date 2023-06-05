//

//  main.cpp

//  pa4

//

//  Created by Zeynep Kurtulus on 22.05.2023.

//


#include <list>

#include <iostream>

#include <pthread.h>

#include <unistd.h>
#include <stdlib.h>
using namespace std;


const int NOT_ALLOCATED = -1;

struct node{
    int heapsize;
    int index;
    int id;
    node *next;
    node(){}
    node(int i, int idx, int hs,  node *n) : id(i), index(idx), heapsize(hs),next(n){}
};

ostream &operator <<(ostream&out, const node &printnode){
     out << "[" << printnode.id << "][" << printnode.heapsize << "][" << printnode.index << "]";
     return out;

}

class HeapManager{
private:

    pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; //Coarse grained lock used to prevent data races on the object
    node * head;

public:

    HeapManager(){ // constructor
        head = new node();
    }
    ~HeapManager(){ // destructor

        destructorHelper(head);
        pthread_mutex_destroy(&mtx);
    }
    void destructorHelper(node *ptr){

        while(ptr != NULL){
            node * itr = ptr;
            ptr = ptr->next;
            delete itr;

        }

    }

    int initHeap(int size){
        head->id = NOT_ALLOCATED;
        head->heapsize = size;
        head->index = 0;
        print();
        return 1;

    }

    void print(){
        node *itr = head; // this will iterate over the entire list
        while (itr != NULL) {
            cout << "[" << itr->id << "][" << itr->heapsize << "][" << itr->index << "]";
            itr = itr->next;
            if(itr != NULL){
                cout << "---";
            }
        }
        cout << endl;

    }

    int myMalloc(int id, int size){

        pthread_mutex_lock(&mtx);
        int idx;
        //cout << "size inside malloc is " << size << endl;
        bool checker = true;
        node *itr = head;
        while(itr != NULL){ // keep going until the end of the list

            if (itr->id == NOT_ALLOCATED && itr->heapsize >= size) { //if it is not alocated and there is enough space

                break;
            
            }
        
                itr = itr->next;
        }

        // at this point we have to check if we have found such space
        if (itr == NULL) {
            cout << "Can not allocate, requested size " << size << " for thread " << id << " is bigger than remaining size" << endl;
            print();
            pthread_mutex_unlock(&mtx);
            return -1;

        }

        else { // if such node is found

            if (itr->heapsize == size) { // if the sizes are the same

                itr->id = id;
                idx = itr->index; // return value

            }

            else{ // if the sizes do not match we have to parse it

                //node* newNode = new node();
                int newIdx = itr->index + size;
                int newSize = itr->heapsize - size;
                itr->id = id;
                itr->heapsize = size;
                node* newNode = new node(NOT_ALLOCATED, newSize, newIdx, itr->next);
                itr->next = newNode;
                idx = itr->index;
            }

            cout << "Allocated for thread " << id << endl;
            print();
            pthread_mutex_unlock(&mtx);
            return idx;
        }

       
    }

    int myFree(int id, int index){
        
        pthread_mutex_lock(&mtx);
        bool checker = true;
        node * left = NULL;
        node *itr = head;
        while(itr!= NULL){

            if(itr->id == id && itr->index == index){
                
                break;
                
            }
            
                left = itr; // left node
                itr = itr->next; // right node
                
        }

        if (itr != NULL) {
            itr->id = NOT_ALLOCATED;// free the node
            node *right = itr->next;
            if(right!= NULL && right->id == NOT_ALLOCATED){
                node *itr2 = right->next;
                itr->heapsize += right->heapsize;
                delete right;
                itr->next = itr2;

            }
            if ( left != NULL && left->id == NOT_ALLOCATED) { // if the left neighbor is also free merge
                left->heapsize += itr->heapsize;
                left->next = itr->next;
                delete itr;

            }
            
            cout << "Freed for thread " << id << "\n";
            print();
            pthread_mutex_unlock(&mtx);
            return 1;
        }
        
        
        else { // we have found such node
            
            cout << "Thread ID: " << id << ", Index: " << index << " could not be found. Free operation failed." << endl;
            print();
            pthread_mutex_unlock(&mtx);
            return -1;
            
            


        }

    }


};
