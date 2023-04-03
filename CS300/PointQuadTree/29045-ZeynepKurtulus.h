//
//  29045-ZeynepKurtulus.hpp
//  the1
//
//  Created by Zeynep Kurtulus on 7.11.2022.
//

#ifndef _9045_ZeynepKurtulus_h
#define _9045_ZeynepKurtulus_h

#include <stdio.h>

#endif /* _9045_ZeynepKurtulus_h*/

#include <string>
#include <iostream>
#include <vector>

using namespace std;


struct node
{
    int x;
    int y;
    
    node(int xx, int yy) //parametric
    {
        x = xx;
        y = yy;
    }
    
    node(){ //default
        x = 0;
        y = 0;
    }
};


class QuadNode{ // to store the information inside the nodes of the tree
public:
    node coordinate;
    string cityname;
    QuadNode *SE;
    QuadNode *NE;
    QuadNode *NW;
    QuadNode *SW;
    
    QuadNode()
    :cityname(""), coordinate(), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
    
    
    QuadNode(const string &cname, node cord, QuadNode *sw, QuadNode *nw, QuadNode *se, QuadNode *ne)
    :cityname(cname), coordinate(cord), SW(sw), NW(nw), SE(se), NE(ne){}
    
    
    friend class QuadTree;
};


class QuadTree{ // to construct and perform operations on the tree
public:
    QuadTree(); // default constructor  ok
    ~QuadTree(); // destructor ok
    void pretty_print(); //ok
    void searchcity(float r, node n); // searches the given city ok
    float calculatedistance(node n1, node n2); // calculates the distance between cities ok
    void insertnode(QuadNode *qn); // inserts a node to quardtree ok 
    void limitsetter(int xmax, int ymax);
    void emptytree(QuadNode *&tobodeleted); // pass by reference so that modifications will apply, accepts root of the tree as param
    
    
    
    
private:
    QuadNode *root; // root of the quadtree
    vector<string> visited; // to store the visited cities while searching
    vector<string> match; // to store the matched cities within radius r
    int x_max; // to keep track of boundry x
    int y_max; // to keep track of boundry y
    
    
    //helpers:
    void prettyprint(QuadNode *currentnode); //ok
    void searchcity(node n, QuadNode *qn, float rad); //ok qn is the pointer where we will start the search, n is the node we're searching for and rad is the radius of the search, so each time we'll send a pointer to start the search from: decomposition we wont have to search the whole quadtree each time 
    string directionsetter(QuadNode *qn1, QuadNode *qn2); //ok
    void emptytree(QuadNode *& qn) const;
    
    
    
    
};
