//
//  29045-ZeynepKurtulus.cpp
//  the1
//
//  Created by Zeynep Kurtulus on 7.11.2022.
//

#include "29045-ZeynepKurtulus.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;


QuadTree::QuadTree(){ // default constructor
    root = NULL;
    y_max = 0;
    x_max =0;
}

void QuadTree::limitsetter(int xmax, int ymax){
    y_max = ymax;
    x_max = xmax;
}


string QuadTree::directionsetter(QuadNode *qn1, QuadNode *qn2){ // decides which direction the tree will extend towards qn1: p qn2: r
    string direction = "";
    if (qn1->coordinate.x < qn2->coordinate.x) { // q1 is the node we will insert q2 is already inserted node
        if (qn1->coordinate.y < qn2->coordinate.y ) { //this is ok
            direction = "SW";
        }
        else if(qn1->coordinate.y > qn2->coordinate.y || qn1->coordinate.y == qn2->coordinate.y){
            direction = "NW";
        }
            
    }
    else if (qn1->coordinate.y < qn2->coordinate.y){ // we know x is not smaller
        direction = "SE";
        if (qn1->coordinate.x == qn2->coordinate.x) {
            direction = "SE";
        }
    }
       
    else if(qn1->coordinate.x > qn2->coordinate.x || qn1->coordinate.x == qn2->coordinate.x || qn1->coordinate.y == qn2->coordinate.y){ // we know that x and y are not smaller
        direction = "NE";
    }
        
    return direction;
}


float QuadTree::calculatedistance(node n1, node n2){
    int dist = sqrt((((n1.x- n2.x)*(n1.x- n2.x)) + ((n1.y - n2.y)*(n1.y - n2.y))));
    return dist;
}


void QuadTree::insertnode(QuadNode *qn){
    string ptrdirection = "";
    if (root == NULL) { // if there is no root i.e tree hasnt been formed yet
        root = qn;
        return;
    }
    
    QuadNode *itr1 = root; // an iterator so that root wont change
    QuadNode *itr2 = NULL;
    
    
    
    while (itr1 != NULL) { // decides where the node will be placed
        ptrdirection = directionsetter(qn, itr1);
        itr2 = itr1;
        if (ptrdirection == "SE")
            itr1 = itr1->SE;
        else if (ptrdirection == "SW")
            itr1 = itr1->SW;
        else if (ptrdirection == "NE")
            itr1 = itr1->NE;
        else if (ptrdirection == "NW")
            itr1 = itr1->NW;
        
    }
    //places the node acc. to the place determined in the while loop
    if (ptrdirection == "NW")
        itr2->NW = qn;
    else if (ptrdirection == "NE")
        itr2->NE = qn;
    else if (ptrdirection == "SW")
        itr2->SW = qn;
    else if (ptrdirection == "SE")
        itr2->SE = qn;
    
}

//private version
void QuadTree::searchcity(node n, QuadNode *qn, float rad){ // n is the cord from query
    if (qn == NULL) { // if no tree is implemented
        return;
    }
    visited.push_back(qn->cityname); // it will add the city name eaxh time we enter this fucntion to search for a city
    if ((n.x -rad >= qn->coordinate.x) && ((n.y + rad) < qn->coordinate.y )){ // region 1 //MODIF
        searchcity(n, qn->SE, rad); // search for the content of node n, starting from the SE pointer within the rad zone 
    }
    else if (((n.x - rad) < qn->coordinate.x  ) && (qn->coordinate.x < (n.x + rad)) && (n.y + rad ) < qn->coordinate.y) { // falls into SE or SW region i.e region 2 OK
        searchcity(n, qn->SE, rad); 
        searchcity(n, qn->SW, rad);
        
    }
    
    else if (((n.x + rad)< qn->coordinate.x) && ((n.y + rad) < qn->coordinate.y)){ // region 3
        searchcity(n, qn->SW, rad);
    }
    else if (((n.x -rad) >= qn->coordinate.x) && (qn->coordinate.y <= (n.y+ rad)) && ((n.y - rad) < qn->coordinate.y)){ // region 4 //MODIF
        searchcity(n, qn->SE, rad);
        searchcity(n, qn->NE, rad);
        
    }
    else if (((n.y- rad)< qn->coordinate.y) && ((n.x + rad) < qn->coordinate.x) && ((n.y+ rad) >= qn->coordinate.y)){ //region 5 MODIF
        searchcity(n, qn->SW, rad);
        searchcity(n, qn->NW, rad);
        
    }
    
    
    else if ((qn->coordinate.x <= (n.x -rad)) && ((n.y -rad) >= qn->coordinate.y)){ //region 6 //MODIF
        searchcity(n, qn->NE, rad);
    }
    else if (((n.y - rad) >= qn->coordinate.y) && ((n.x - rad) < qn->coordinate.x) && ((n.x +rad) >= qn->coordinate.x)){ // region 7 //MODIF
        searchcity(n, qn->NE, rad);
        searchcity(n, qn->NW, rad);
        
    }
   
    else if (((n.y - rad) >= qn->coordinate.y) && (qn->coordinate.x > (n.x+rad))){ //region 8 //MODIF geri alındı deniyorum 
        searchcity(n, qn->NW, rad);
    }
    
    else if (calculatedistance(qn->coordinate, n) > rad && n.y < qn->coordinate.y && n.x > qn->coordinate.x && n.x- rad < qn->coordinate.x){ // region 9 //MODIF
        searchcity(n, qn->SE, rad);
        searchcity(n, qn->SW, rad);
        searchcity(n, qn->NE, rad);
    }
    
    else if (n.x < qn->coordinate.x && qn->coordinate.y > n.y && rad < calculatedistance(qn->coordinate, n)){ //region 10
        searchcity(n, qn->SE, rad);
        searchcity(n, qn->SW, rad);
        searchcity(n, qn->NW, rad);
        
    }
    
    else if (calculatedistance(qn->coordinate, n) > rad && n.x > qn->coordinate.x && n.y > qn->coordinate.y){ //region 11
        
        searchcity(n, qn->SE, rad);
        searchcity(n, qn->NE, rad);
        searchcity(n, qn->NW, rad);
    }
    
    else if (calculatedistance(qn->coordinate, n) > rad && qn->coordinate.x > n.x && qn->coordinate.y < n.y){ // region 12
        searchcity(n, qn->SW, rad);
        searchcity(n, qn->NE, rad);
        searchcity(n, qn->NW, rad);
    }
    
    else if (calculatedistance(qn->coordinate, n) <= rad){ // region 13
        
        match.push_back(qn->cityname); // I will have found a city since  region 13 covers all the areas
        searchcity(n, qn->SE, rad);
        searchcity(n, qn->SW, rad);
        searchcity(n, qn->NE, rad);
        searchcity(n, qn->NW, rad);
    }
    
}

// private version
void QuadTree::prettyprint(QuadNode *itr){
    if (itr == NULL) { // empty tree
        return;
    }
    else if (itr != NULL){
        cout << itr->cityname << endl; // to print out the city at the root
        //RECCURSIVE CALLS
        prettyprint(itr->SE);
        prettyprint(itr->SW);
        prettyprint(itr-> NE);
        prettyprint(itr-> NW);
        
    }
}


void QuadTree::pretty_print(){
    prettyprint(this->root);
}

//public version
void QuadTree::searchcity(float r, node n){
    searchcity(n, this->root, r); // n is the node from query this-> root is the root of the tree which is the initial startign point of our search 
    unsigned long int vecsize = match.size(); // num of the founded cities
    unsigned long int vecsize2 = visited.size(); //num of the visited cities
    
    for(unsigned long int k = 0; k < vecsize ; k ++){
        if (k == 0) {
            cout << match[k];
        }else
            cout << ", " << match[k];
        
    }
    cout << endl;
    if (vecsize == 0) { // no match city within range r
        cout << "<None>" << endl;
    }

    for(unsigned long int i = 0; i < vecsize2; i++){
        if (i == 0) {
            cout << visited[i];
        }
        else
            cout << ", " << visited[i];
        
    }
    cout << endl << endl;
    match.clear(); // to empty the vectors
    visited.clear(); // to empty the vectors
}


void QuadTree::emptytree(QuadNode *&tobedeleted){ 
    
    if (tobedeleted != NULL) {
        emptytree(tobedeleted->NW);// deletes all the NW nodes
        emptytree(tobedeleted->NE);// deletes all the NE nodes
        emptytree(tobedeleted->SW);// deletes all the SW nodes
        emptytree(tobedeleted->SE); // deletes all the SE nodes
    }
    delete tobedeleted;
}



QuadTree::~QuadTree(){ // destructor
    emptytree(root);
}
