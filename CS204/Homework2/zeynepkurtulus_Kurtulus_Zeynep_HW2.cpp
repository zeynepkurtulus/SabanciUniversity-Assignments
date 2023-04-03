#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW1_strutils.h"
#include <cctype>
using namespace std;

struct node{
    char ch;
    node * next; // pointer to the next node
    node() // defaut constructor
    {
    }
    node(char c, node * n)// constructor
      :ch(c), next(n)
    {};
};


bool ifcharexists(node * itr1, char searched){ // returns false if the char does not exist
    bool v = false;
    while (itr1 != NULL && v == false) { // keep going until the end of the list
        if (itr1->ch == searched) {
            v = true;
            //itr1 = itr1->next;
        }
        else{
            itr1 = itr1->next;
        }
        
    }
    return v;
}
 
bool commandchecker(string command){ // checks if the commands are valid
    bool v1 = false;
    if (command == "sim" || command == "del1" || command == "insert1" || command == "insert2" || command == "del2" || command == "exit") {
        v1 = true;
    }
    return v1;
}

void displaylist(node *ittirator){
    while (ittirator != NULL) {
        cout << ittirator->ch;
        ittirator = ittirator->next;
    }
}

void terminate(node * itr){
    node *temp = itr;
    while (itr != NULL) { // until the end of the list
        itr = temp->next;
        delete temp;
        temp = itr;
    }
}

int main(){
    bool goOn = true;
    ifstream input1, input2;
    string line1, line2, filename1, filename2, command, l1, l2, str1, str2;
    char d1, d2, i11, i12, i22, i21;
    cout << "Please enter file 1 name: ";
    cin >> filename1;
    input1.open(filename1.c_str());
    
    while (input1.fail()) {
        cout << "Please enter file 1 name: ";
        cin >> filename1;
        input1.open(filename1.c_str());
    }
    cout << "Please enter file 2 name: ";
    cin >> filename2;
    input2.open(filename2.c_str());
    
    while (input2.fail()) {
        cout << "Please enter file 2 name: ";
        cin >> filename2;
        input2.open(filename2.c_str());
    }
    
    node * head1 = new node; // head node for linklist1 => will stay ath the same location
    node * head2 = new node; // head node for linklist2 => will stay at the same location
    head1 = NULL; // initialized head node to null
    head2 = NULL;
    node * itr1; // ittirate over list1 => will keep moving
    node * itr2; // ittirate over list2 => will keep moving
    while(getline(input1, line1)){
        char ch = line1[0]; //so that it only takes the letters
        node * newNode = new node(ch, NULL);
        if(head1 == NULL){ // if head node does not exist
            head1 = newNode; // create the head node
            itr1 = head1; // set the ittirated to the head node so, it will stay at the beginning and ittirate over the whole list
        }
        else{ // if the head node exist
            itr1->next = newNode; // connect the ittirator to the next node
            itr1 = itr1->next; // ittirator is now assigned at the next node => it keeps moving
        }
    }
    itr1 = head1; // to take ittirator at the beginning
    
    while(getline(input2, line2)){
        char ch = line2[0];
        node * newNode2 = new node(ch, NULL);
        if(head2 == NULL){ // if head does not exist
            head2 = newNode2; // create the head
            itr2 = head2; // set the ittirator to the head node so it can ittirate over the whole list
        }
        else{ // if head does exist
            itr2->next = newNode2; // connect the ittirator to the next node
            itr2 = itr2->next; //  ittirator is now assigned at the next node => it keeps moving
        }
    }
    itr2 = head2; // take the ittirator to the beginning

    cout << "List1: ";
    displaylist(itr1);
    cout << endl;
    cout << "List2: ";
    displaylist(itr2);
    cout << endl;

    cout << endl;
    cin.ignore();
    while (goOn) { // keep asking until the user enters exit
        cout << "Enter a command and its corresponding argument(s), if any: "; // store the command and arguments
        getline(cin, str1);
        stringstream iss1(str1);
        iss1 >> command; // just stores the command

        
        // checks the validity of the commands
        while (commandchecker(command) == false) { // keep asking for command if invalid
            cout << "Invalid command." << endl << endl;
            cout << "Enter a command and its corresponding argument(s), if any: ";
            getline(cin, str1);
            istringstream iss1(str1);
            iss1 >> command;
        }
        
        //command is true for sure since it passed the loop it will begin to check the validty of the arguments
            
            bool dv = true;
            istringstream iss2(str1);
            while (command == "del1" && dv) {
                iss2 >> command >> d1;
                dv = false;
                while (!islower(d1) && command == "del1") {
                    dv = true;
                    cout << "Invalid arguments." << endl << endl;
                    cout << "Enter a command and its corresponding argument(s), if any: ";
                    getline(cin, str1);
                    istringstream iss2(str1);;
                    iss2 >> command >> d1;
                }

            }
            bool dv1 = true;
            while (command == "del2" && dv1){
                istringstream iss3(str1);
                iss3 >> command >> d2;
                dv1 = false;
                while (!islower(d2) && command == "del2") {
                    dv1 = true;
                    cout << "Invalid arguments." << endl << endl;
                    cout << "Enter a command and its corresponding argument(s), if any: ";
                    getline(cin, str1);
                    istringstream iss3(str1);;
                    iss3 >> command >> d2;
                }
                
            }
            bool ins = true;
            while (command =="insert1" && ins){
                istringstream iss4(str1);
                iss4 >> command >> i11 >> i12;
                ins = false;
                while ((!islower(i11) || !islower(i12)) && command == "insert1") {
                    ins = true;
                    cout << "Invalid arguments." << endl << endl;
                    cout << "Enter a command and its corresponding argument(s), if any: ";
                    getline(cin, str1);
                    istringstream iss4(str1);
                    iss4 >> command;
                    if (command == "insert1") {
                        iss4 >> i11 >> i12; // i11 = insert edilecek char - i12 = location
                    }
                }
            }
            bool ins1 = true;
            while (command == "insert2" && ins1){
                istringstream iss5(str1);
                iss5 >> command >> i21 >> i22;
                ins1 = false;
                while (!islower(i21) && !islower(i22) && command == "insert2" && ins1) {
                    ins1 = true;
                    cout << "Invalid arguments." << endl << endl;
                    cout << "Enter a command and its corresponding argument(s), if any: ";
                    getline(cin, str1);
                    istringstream iss5(str1);
                    iss5 >> command;
                    if (command == "insert2") {
                        iss5 >> i21 >> i22;
                    }
                }
            }
            if (command == "exit"){ // dont forget to clean all the lists !!
                cout << "Clearing the two lists and saying Goodbye!" << endl;
                terminate(itr1);
                terminate(itr2);
                goOn = false; // terminate the loop if the user enters "exit"
            }
        
        // SIM OPERATION
        
        else if (command == "sim") { // SORUN VAR
            int sameplace = 0;
            cout << "Displaying the contents of the two lists:" << endl;
            cout << "List1: "; // DISPLAY LIST1
            if (itr1 != NULL) {
                displaylist(itr1);
            }
            
            //itr1 = head1; // take the itr1 to the beginning
            cout << endl;
            cout << "List2: "; // DISPLAY LIST2
            //itr2 = head2;
            if (itr2 != NULL) {
                displaylist(itr2);
            }
            while (itr1 != NULL && itr2 != NULL) { // until the end of both lists
                if (itr1->ch == itr2->ch) { // checks just for the first node
                    sameplace++;
                    itr1 = itr1->next;
                    itr2 = itr2->next;
                }
                else{ // if the chars do not match
                    itr1 = itr1->next;
                    itr2 = itr2->next;
                }
            }
            itr1 = head1;
            itr2 = head2;
            cout << endl;
            cout << "There is/are " << sameplace << " letter(s) matched in the same position in both lists." << endl << endl;
        }
        
        
        //  DELETE OPERATION
        else if (command == "del1"){
            node *temp = itr1;
            node *tobedeleted = temp->next;
           
            if(!ifcharexists(itr1, d1)){ // if the char does not exist in the word
               cout << "No deletion as the value " << d1 << " was not found in the list.";
            }
            else{
                while(temp!=NULL) {
                      if(temp->ch == d1){
                          tobedeleted = temp;
                          node *ptr;
                         if(tobedeleted == itr1) { //if the searched char is in head
                             itr1 = itr1->next;
                            delete tobedeleted; // delete head node
                             //if(itr1 == NULL){ // if it is at the end of the list
                                 //tobedeleted = NULL;
                             //}else{
                               //  tobedeleted = itr1; // it it is somewhere other than head and end
                             //}
                         } else {
                             ptr = itr1;
                             while (ptr->next != tobedeleted) {
                                 ptr = ptr->next;
                             }
                             ptr->next = tobedeleted->next;
                            delete tobedeleted;
                         }
                      }
                    temp = temp->next;
                   }
                cout << "Deleting all occurrences of " << d1<< " in List1." << endl;
                cout << "The current content of List1 is: ";
                displaylist(itr1);
            }
            //itr1 = head1;
            cout << endl << endl;
            
        }
        else if (command == "del2"){
            node *temp2 = itr2;
            node *tobedeleted2 = itr2;
            
            if(! ifcharexists(itr2, d2)){ // if the char does not exist in the word
                cout << "No deletion as the value " << d1 << " was not found in the list.";
            }
            else{
                
                while(temp2!=NULL) {
                      if(temp2->ch == d2){
                          tobedeleted2 = temp2;
                          node *ptr2;
                         if(tobedeleted2 == itr2) {
                            itr2 = itr2->next;
                            delete tobedeleted2;
                             //if (itr2 == NULL) {
                              //  tobedeleted2 == NULL;
                            //}
                             //else{
                               //tobedeleted2 = itr2;
                             //}
                         } else {
                             ptr2 = itr2;
                             while (ptr2->next != tobedeleted2) {
                                 ptr2 = ptr2->next;
                             }
                             ptr2->next = tobedeleted2->next;
                             delete tobedeleted2;
                         
                      }
                   }
                    temp2 = temp2->next;
                }
        
                cout << "Deleting all occurrences of " << d2 << " in List2." << endl;
                cout << "The current content of List2 is: ";
                displaylist(itr2);
                    
            }
            cout << endl << endl;
            
    }
        // INSERT OPERATION
        
        else if (command == "insert1"){
            cout << "Inserting " << i11 << " after " << i12 << " in List1." << endl;
            if (! ifcharexists(itr1, i12)) // if the characther does not exist append it to the head
            {
                itr1 = head1;
                cout << "The node with " << i12 << " value does not exist. Therefor, Inserting " << i11 << " at the beginning of the list." << endl;
                node *insertnode = new node(); // created a new node to insert
                insertnode->ch = i11; // assign the new char
                insertnode->next = itr1; // make it the head
                itr1 = insertnode; // take the head to the beginning
                head1 = itr1;
                cout << "The current content of List1 is: ";
                displaylist(itr1);
                cout << endl << endl;
            }
            else // if the characther exists
            {
                itr1 = head1;
                bool checker = true;
                bool b = true;
                cout << "The node with " << i11 << " has been inserted after the first occurrence of a node with " << i12 << " value." << endl;
                while (itr1->ch == i12 && checker) { // if the searched characther is at the beginning of the list
                    checker = false;
                    node *tobeinserted = new node();
                    tobeinserted->ch = i11;
                    tobeinserted->next = itr1->next;
                    itr1->next = tobeinserted;
                    b = false;
                }
                if (b) {
                    while (itr1->next->ch != i12 && checker) {
                        itr1 = itr1->next; // keep moving the ittirator until the searched char is found
                    }
                    node * tobeinserted = new node(); // created the node that will be inserted
                    tobeinserted->ch = i11; // assigned the char
                    tobeinserted->next = itr1->next->next; // stores the address of the next node so we wont lose it
                    itr1->next->next = tobeinserted;
                }
                cout << "The current content of List1 is: ";
                itr1 = head1;
                displaylist(itr1);
                cout << endl << endl;
            }
               
            
            
        }
        else if (command == "insert2"){
            cout << "Inserting " << i21 << " after " << i22 << " in List2." << endl;
            //displaylist(itr2);
            if (! ifcharexists(itr2, i22)) // if the characther does not exist append it to the head
            {
                //itr2 = head2;
                cout << "The node with " << i22 << " value does not exist. Therefor, Inserting " << i21 << " at the beginning of the list." << endl;
                node *insertnode2 = new node(); // created a new node to insert
                insertnode2->ch = i21; // assign the new char
                insertnode2->next = itr2; // make it the head
                itr2 = insertnode2; // take the head to the beginning
                head2 = itr2;
                cout << "The current content of List2 is: ";
                while (itr2 != NULL) { // demekki bir tane daha node var ve o node bos
                    cout << itr2->ch;
                    itr2 = itr2->next;
                }
                //displaylist(head2);
                cout << endl << endl;
            }
            else // if the characther exists
            {
                bool z = true;
                bool checker = true;
                cout << "The node with " << i21 << " has been inserted after the first occurrence of a node with " << i22 << " value." << endl;
                while (itr2->ch == i22 && checker) { // if the searched characther is at the beginning of the list
                    checker = false;
                    node *tobeinserted2 = new node();
                    tobeinserted2->ch = i21;
                    tobeinserted2->next = itr2->next;
                    itr2->next = tobeinserted2;
                    z = false;
                }
                if (z) {
                    while (itr2->next->ch != i22 ) { // ya head  de varsa ??
                        itr2 = itr2->next; // keep moving the ittirator until the searched char is found
                    }
                    node * tobeinserted2 = new node(); // created the node that will be inserted
                    tobeinserted2->ch = i21; // assigned the char
                    tobeinserted2->next = itr2->next->next; // stores the address of the next node so we wont lose it
                    itr2->next->next = tobeinserted2;
                }
              
                cout << "The current content of List1 is: ";
                displaylist(itr2);
                cout << endl << endl;
            }
            
            
        }
        

    }
    
    
    return 0;
}
