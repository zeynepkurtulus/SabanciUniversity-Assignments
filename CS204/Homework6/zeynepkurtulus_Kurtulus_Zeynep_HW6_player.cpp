//
//  zeynepkurtulus_Kurtulus_Zeynep_HW6_player.cpp
//  zeynepkurtulus_Kurtulus_Zeynep_HW6
//
//  Created by Zeynep Kurtulus on 15.05.2022.
//
#include <string>
#include <iostream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_player.h"
using namespace std;

template <class type>
Player<type>::Player(Board<type> &boardmatrix) // parametric constructor => we must use initializer lists here
: myboard(boardmatrix), current_id(next_id)
{
    next_id++;
}


template <class type>
bool Player<type>::updateCell(int r, int c, const type &v)
{
    bool validator = true;
    if ((this->current_id == myboard.getid(r,c)) || ( myboard.getid(r,c) == 0))
    {
        int id = this->current_id; // player id si olalı
        myboard = myboard.updatehelper(r, c, v); // fill the content of that cell
        myboard = myboard.ownerhelper(r, c, id);
    }
    else
    {
        validator = false;
    }
    return validator;
}

template <class type>
void Player<type>::updateMyCells(int updatevalue)
{
    for (int i = 0; i < myboard.getrows(); i++) {
        for (int j = 0; j < myboard.getcols(); j++) {
            if (myboard.getid(i,j) == this->current_id) {
                myboard.updatehelper(i, j, updatevalue);
            }
        }
    }
}

template <class type>
bool Player<type>::unclaimOwnership(int r, int c)
{
    bool validator = true;
    if (this->current_id ==  myboard.getid(r,c)) //if the cell is currently owned by that player calling the function
    {
        myboard.ownerhelper(r, c, 0); // unclaims the ownership of that cell
    }
    else if (this->current_id != myboard.getid(r, c)) // if the cell is not owned by the player calling the function
    {
        validator = false;
    }
    return validator;
}

template <class type>
void Player<type>::unclaimOwnerships()
{
    for (int i = 0; i < myboard.getrows(); i++) {
        for (int j = 0; j < myboard.getcols(); j++) {
            if (myboard.getid(i,j)== this->current_id) // if that cell is owned by the calling player
            {
                myboard.ownerhelper(i, j, 0); // unclaim the ownership of the cell
            }
        }
    }
}
