//
//  decompress.cpp
//  decompress
//
//  Created by Zeynep Kurtulus on 23.12.2022.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

 

int main() {
    
    string inputfile = "compout", outfile = "decompout", prev, curr;
    int count = 0, codestor;
    ifstream input;
    ofstream out;
    input.open(inputfile.c_str());
    out.open(outfile.c_str());
    string dict[4096];
    int size = 255; // maps the codes
    for (int i = 0; i <= size; i++) {
        dict[i] = string(1, (unsigned char)i);
    }
    while (input >> codestor) {
        if (count == 0) {
            prev = dict[codestor];
            out << dict[codestor];
            
        }
        if (count != 0) {
            if (dict[codestor] == "") { // value not in dict
                size++;
                dict[size] = prev + prev[0];
                out << dict[size];
            }
            else{ //value not in dict
                out << dict[codestor];
                size++;
                dict[size] = prev + dict[codestor][0];
            }
           
        }
        count++;
        prev = dict[codestor];
        
    }
    
    return 0;
}
