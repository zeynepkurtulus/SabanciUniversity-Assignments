//
//  TwoDLinkedList.cpp
//  zeynepkurtulus_Kurtulus_Zeynep_HW3
//
//  Created by Zeynep Kurtulus on 25.03.2022.
//

#include <stdio.h>
#include "TwoDLinkedList.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

TwoDLinkedList::TwoDLinkedList() // constructor sets the head to NULL
{
    head = NULL;
}

void TwoDLinkedList::add_row_sorted(string str)
{
    str.erase(remove(str.begin(), str.end(), '\r'), str.end() );
    bool checker = false;
    node *itr = head; // eklenecek node a itr2 de
    node *head2 = NULL;
    node *itr2 = NULL;
    bool firstline = false;


        if (head == NULL) { // creates just the first list
            for (int j = 0; j < str.length(); j++) {
                char ch = str.at(j);
                node *newnode = new node(ch, NULL, NULL);
                if (head == NULL) {
                    head = newnode; // set the head node
                    itr = head;
                    firstline = true; // first line exists
                }
                else{
                        itr->right = newnode;
                        itr = itr->right;
                    }
            }
            itr = head;
        }
        else // if the first lis is created
        {


            for (int i = 0; i < str.length(); i++) {
                char c = str.at(i);
                node *newNode = new node(c, NULL, NULL);
                if (head2 == NULL) {
                    head2 = newNode; // head of the new list
                    itr2 = head2; // ittirates of the new list
                    //itr->down = itr2;
                }
                else{
                    itr2->right = newNode;
                    itr2 = itr2->right;
                }
            }
        while (itr->down != NULL) {
            while (itr->data < itr2->data) {
                itr = itr->down;
                }
            }
            itr->down = itr2;
        }
    itr = head;
    itr2 = head2;
    while (itr->down != NULL) {
        while (itr->data < itr2->data) {
            itr = itr->down;
        }
    }
    if (itr->down != NULL) {
        if (itr->data > itr2->data) {
            while (itr != NULL) {
                if (itr == head) {
                    head = itr2;
                }
                else{
                    itr2->down = itr;
                    itr = itr->right;
                    itr2 = itr2->right;
                }
                
            }
        }
       
    }
    
    
}
