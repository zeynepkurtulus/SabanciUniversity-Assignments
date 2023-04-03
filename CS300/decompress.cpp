//
//  decompress.cpp
//  ziv-lempel
//
//  Created by Zeynep Kurtulus on 21.12.2022.
//

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;







int main(){
    //const int size = 4096;
    string mytable[4096];
    string prevstr, currstr;
    int idx = 1, limit = 256, prev, curr;
    ifstream input;
    ofstream out;
    string fn = "compin", outname = "decompout";
    input.open(fn.c_str());
    out.open(outname.c_str());
    for (idx = 1; idx < limit; idx++) {
        string str;
        char ch = char(idx);
        str = ch;
        mytable[idx] = str;
    }
    input >> curr;
    out << mytable[curr];
    
    while (!input.eof()) {
        prev = curr;
        input >> curr;
        if (mytable[curr].empty()) { // is not in the hash table
            prevstr = mytable[prev];
            currstr = mytable[prev][0];
            string append = prevstr + currstr;
            out << append;
            mytable[idx] = append;
            idx++;
        }
        else{ // element exits
            out << mytable[curr];
            prevstr = mytable[prev];
            currstr = mytable[curr][0];
            string append = prevstr + currstr;
            mytable[idx] = append;
            idx++;
            
        }
    }
    
    return 0;
}
