//
//  hashtable.cpp
//  ziv-lempel
//
//  Created by Zeynep Kurtulus on 21.12.2022.
//
#include "hashtable.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
//ascii initialization
void dictionary(int& idx, hashtable<string>& mytable){
    for (idx = 1; idx < 256; idx++) {
        string str;
        char ch = char(idx);
        str = ch;
        mytable.insert(str, idx);
        
    }
}



int main()
{
    hashtable<string> myhash("ITEM_NOT_FOUND");
    ifstream input;
    ofstream output;
    string fn = "compin", outname = "compout", curr, prev, pcur;
    input.open(fn.c_str());
    output.open(outname.c_str());
    int idx = 1;
    dictionary(idx, myhash);
    char initial; //input char
    while (input.get(initial)) {
        curr = initial;
        pcur = prev + curr;
        if (myhash.find(pcur) == -1) { // if not found
            if (myhash.isFull()) {
                myhash.insert(pcur, idx);
                idx++;
            }
        }
        else if (myhash.find(pcur) != -1){ // if exists
            prev = pcur;
        }
        
        output << myhash.find(prev) << " ";
        prev = curr;
        
    }
    
    output << myhash.find(prev);
    
    
    
    
    return 0;
}


