//
//  hashtable.hp
//  ziv-lempel
//
//  Created by Zeynep Kurtulus on 21.12.2022.
//

#ifndef hashtable_h
#define hashtable_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

template <class hashobj>
class hashtable {
    
public:
    hashtable<hashobj>(const hashobj& notexits, int size = 4096); //constructor
    bool isFull() const ; //cheks if there is space returns true if there is space in the table
    void insert(const hashobj& insertval, int &x);
    int find(const hashobj& search); //find search in the table if not found return -1

private:
    int findpos(const hashobj& search) const;
    struct HashNode{
        hashobj element;
        int k;
        
    };
    int currentsize;
    const hashobj ITEM_NOT_FOUND;
    vector <HashNode> hasharray;
};

template <class hashobj>
hashtable<hashobj>::hashtable(const hashobj& notexist, int size)
    :ITEM_NOT_FOUND(notexist), hasharray(size), currentsize(0){
        for (int i = 0; i < hasharray.size(); i++) {
            hasharray[i].element =  ITEM_NOT_FOUND;
        }
    }


template <class hashobj>
int hashtable<hashobj>::findpos(const hashobj& searched) const{
    int tempPos = hash<hashobj>{}(searched);
    tempPos %= hasharray.size();
    
    while (hasharray[tempPos].element != ITEM_NOT_FOUND && hasharray[tempPos].element != searched) {
        tempPos++;
        if (tempPos >= hasharray.size()) {
            tempPos = tempPos - hasharray.size();
        }
    }
}

template <class hashobj>
int hashtable<hashobj>::find(const hashobj &search) {
    int cuurentpos = findpos(search);
    if (hasharray[cuurentpos].element == search) {
        int k = hasharray[cuurentpos].k;
        return k;
    }
    else{
        return -1; // element does not exist
    }
}

template <class hashobj>
bool hashtable<hashobj>::isFull() const{
    bool validator = false;
    if (currentsize + 1 < hasharray.size()) {
        validator = true;
    }
    return validator;
    
}

template <class hashobj>
void hashtable<hashobj>::insert(const hashobj& insertval, int& x){
    int pos = findpos(insertval);
    if (hasharray[pos].element != insertval) { // if the element does not exist consruct a struct
        hasharray[pos].k = x;
        hasharray[pos].element = insertval;
        currentsize++; // increase the size for insertion
    }
}



#endif /* hashtable_h */
