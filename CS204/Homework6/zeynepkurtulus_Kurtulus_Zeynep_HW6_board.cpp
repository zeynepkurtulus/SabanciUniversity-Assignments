//
//  zeynepkurtulus_Kurtulus_Zeynep_HW6_board.cpp
//  zeynepkurtulus_Kurtulus_Zeynep_HW6
//
//  Created by Zeynep Kurtulus on 15.05.2022.
//
#include <string>
#include <iostream>
#include <iomanip>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_board.h"

using namespace std;

template <class type>
Board <type>::Board(int r, int c) // parametric constructor: Member of the Board<boardtype> class
{
    rows = r;
    cols = c;
    mymat = new Cell<type>*[rows]; // pointer of type cell and mymat points to this pointer
    for (int i = 0; i < rows; i++) { // dynamically allocated matrix
        mymat[i] = new Cell<type>[cols];
    }
    
    // initialize the ownership
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            mymat[i][k].owner = 0;
        }
    }
    
}

template <class type>
Board<type>::Board(const Board & copy)// deep copy constructor
{
    rows = copy.rows;
    cols = copy.cols;
    mymat = new Cell<type>*[rows];
    for (int i = 0; i < rows; i++) {
        mymat[i] = new Cell<type>[cols];
    }
    
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            mymat[i][k] = copy.mymat[i][k];
        }
    }
    
}

template <class type>
Board<type>::~Board() // destructor
{
    for (int i = 0; i < rows; i++) {
        delete [] mymat[i]; // deletes the pointer points to the i th row
        mymat[i] = NULL; // sets the pointer to pointer to null
    }
}

template <class type>
void Board<type>::displayBoard() // displays the content of the board
{
    cout << "Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE):" << endl;
    for (int j = 0; j < cols; j++) {
        cout << "       "<<j << "      ";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        cout << i;
        for (int k = 0; k < cols; k++) {
            cout << "    " << "(" << mymat[i][k].owner << "," << mymat[i][k].value << ")" << "     ";
        }
        cout << endl;
    }
}

template <class type>
void Board<type>::updateBoardCells(int id, type updatedvalue)
{
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            if (mymat[i][k].owner == id) { // if that cells owner matches the id
                mymat[i][k].value = updatedvalue; // update the value of that cell 
            }
        }
    }
}

template <class type>
int Board<type>::knowTheOwner(int r, int c) // returns the owner of the cell
{
    if (mymat[r][c].owner != 0) { // if the cell is owned
        return mymat[r][c].owner; // return the owner
    }
    else // if the cell is not owned
        return 0; // return 0
}

template <class type>
int Board<type>::getPlayerCellsCount(int id)
{
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            if (mymat[i][k].owner == id) {
                count++;
            }
        }
    }
    return count;
}

template <class type>
int Board<type>::getrows()
{
    return rows;
}

template <class type>
int Board<type>::getcols()
{
    return cols;
}

template <class type>
int Board<type>::getid(int r, int c)
{
    int num = mymat[r][c].owner;
    return num;
}

template <class type>
type Board<type>::getvalue(int r, int c)
{
    return mymat[r][c].value;
}


template <class type>
Board<type> &Board<type>::updatehelper(int r, int c, const type v)
{

    this->mymat[r][c].value= v;
    return *this;
}

template <class type>
Board<type> & Board<type>::ownerhelper(int r, int c, int o)
{
    this->mymat[r][c].owner = o;
    return *this;
    
}
