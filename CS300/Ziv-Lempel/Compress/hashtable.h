//
//  hashtable.h
//  compress
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

struct HashNode{
    string key;
    int code;
    
    HashNode(){
        key = "";
        code = -1; // indicates no code set
    }
    HashNode(string k, int c){
        key = k;
        code = c;
    }
    
    HashNode(string onlyk){
        key = onlyk;
        code = -1;
    }
    bool operator!=(const HashNode& rhs) const{
        return this->key != rhs.key;
    }
    
    bool operator==(const HashNode&rhs) const{
        return this->key == rhs.key;
    }
};




template <class hashobj>
class hashtable {
    
public:
    explicit hashtable(const hashobj& notexits, int size = 4096); //constructor
    hashtable(const hashtable&rhs)
        :ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),hasharray(rhs.hasharray), currentsize(rhs.currentsize){}

    void insert(const hashobj& insertval);
    const hashobj& find(const hashobj& search) const; //find search in the table
    enum entryinfo { active, deleted, empty };
    void remove(const hashobj& removeobj);
    
    
private:
    
    
    
    struct hashentry{
        hashobj element;
        entryinfo info;
        hashentry(const hashobj& obj = hashobj(), entryinfo ei = empty)
            :element(obj), info(ei){}
    };
    
    
    int currentsize;
    const hashobj ITEM_NOT_FOUND;
    vector <hashentry> hasharray;
    bool isActive(int currpos) const;
    int hashfunc(const hashobj& obj, int size) const;
    int findpos(const hashobj& search) const;
};



///IMPLEMENTATIONS BELOW

template <class hashobj>
hashtable<hashobj>::hashtable(const hashobj& notexist, int size)
    :ITEM_NOT_FOUND(notexist), hasharray(size){}

template <class hashobj>
int hashtable<hashobj>::hashfunc(const hashobj &obj, int size)const{
    int sum = 0;
    int limit = obj.key.length();
    for (int i =0; i < limit; i ++) {
        sum = sum +(unsigned char)obj.key[i];
    }
    if (obj.key.length() != -1 && sum % size <= 255) {
        return 255;
    }
    return (sum%size);
}





template <class hashobj>
int hashtable<hashobj>::findpos(const hashobj& searched) const{
    
    int pos = hashfunc(searched, hasharray.size());
    while (hasharray[pos].element != searched  && hasharray[pos].info != empty) {
        pos+=1;
        if (pos >= hasharray.size()) {
            pos -= hasharray.size();
        }
    }
    return pos;
}


template <class hashobj>
void hashtable<hashobj>::insert(const hashobj& insertval){
    int pos = findpos(insertval);
    if (isActive(pos)) { // if the element does not exist consruct a struct
        return;
    }else{
        hasharray[pos] = hashentry(insertval, active); // creared a node
        
    }
}




template <class hashobj>
const hashobj& hashtable<hashobj>::find(const hashobj &search) const{
    int cuurentpos = findpos(search);
    if (isActive(cuurentpos)) {
        
        return hasharray[cuurentpos].element;
    }
    else{
        return ITEM_NOT_FOUND; // element does not exist
    }
}


template <class hashobj>
void hashtable<hashobj>::remove(const hashobj &removeobj){
    int pos = findpos(removeobj);
    if (isActive(pos)) {
        hasharray[pos].info = deleted;
    }
}


template <class hashobj>
bool hashtable<hashobj>::isActive(int currpos)const{
    return hasharray[currpos].info == active;
    
}




#endif /* hashtable_h */
