//
//  main.cpp
//  compress
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




int main()
{
    ifstream input;
    ofstream out;
    string inputfile = "compin.txt", outfile = "compout.txt", notexist; //notexists stringnotin hash
    input.open(inputfile.c_str());
    out.open(outfile.c_str());
    const int limit = 4096;
    bool validator = true;
    int counter = 255; // our table will start from 256
    HashNode node;//dummyobj
    hashtable<HashNode> myhash = hashtable<HashNode>(node, limit); //hassh array
    // initialized ascii codes
    for (int i = 1; i < 256; i++) {
        string str = string(1,char(i));
        HashNode asciobj(str, i);
        myhash.insert(asciobj);
    }
    string merger = "";
    char chstor;
    while (validator) {
        input.get(chstor); //get char by char
        if (input.eof()) {
            validator = false;
        }
        if (validator) {
            merger += chstor; //merer stringjoin valıe
            HashNode notin(merger); //notin newObjectNotInHashTable
            if (myhash.find(notin) == node) {
                counter++;
                notin.code = counter;
                myhash.insert(notin);
                notexist = merger.substr(0, merger.length()-1);
                HashNode node2(notexist); //objnotinhash
                node2 = myhash.find(node2);
                merger = string(1,merger.back());
                
                out << node2.code << " ";
            }
        }
        
    }
    
    
    HashNode lastelem(merger);
    lastelem = myhash.find(merger);
    
    //check if it is in the hash table
    if (lastelem != node) {
        out << lastelem.code;

    }
    
    
    return 0;
}


