// Zeynep Kurtulus 29045
//  29045-ZeynepKurtulus-main.cpp
//

#include <stdio.h>
#include "29045-ZeynepKurtulus.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;



int main(){
    string fn1 = "cities.txt", fn2 = "queries5.txt", line, line2, cityname, query_xstor, query_ystor, radiusstor, linestorage;
    int xcord = 0, ycord = 0, counter = 0, query_x, query_y;
    float radius;
    QuadTree quadtree = QuadTree(); // generated a Quadtree object
    ifstream input, input2;
    input.open(fn1.c_str()); //open the cities file
    input2.open(fn2.c_str()); // open the queries file
    while (getline(input, line)) {
        istringstream iss1(line);
        if (counter == 0) { // just for the first line
            iss1 >> xcord >> ycord; // assigned the measres of the coordinate system
            quadtree.limitsetter(xcord, ycord); // assigned the maximum values of x and y
            counter++;
        }
        else{ // for the rest of the lines
            iss1 >> cityname >> xcord >> ycord;
            QuadNode *node = new QuadNode(); // generated a new node
            node->coordinate.x = xcord;
            node->coordinate.y = ycord;
            node->cityname = cityname;
            quadtree.insertnode(node);
        }
        
    }
    input.clear();
    quadtree.pretty_print(); // prints the formed point quadtree
    cout << endl;
    while (getline(input2, line2)) { // for the queries txt
        istringstream iss2(line2);
        
        getline(iss2,query_xstor, ','); // to get rid of the commas
        query_x = stoi(query_xstor); //string to int
        
        getline(iss2,query_ystor, ','); // to get rid of the commas
        query_y = stoi(query_ystor); //string to int
        
        getline(iss2,radiusstor, ','); // to get rid of the commas
        radius = stof(radiusstor); // string to float
        
        node n = node(query_x, query_y);
        quadtree.searchcity(radius, n);
    }
    return 0;
}
