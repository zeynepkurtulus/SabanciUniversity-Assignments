//
//  zeynepkurtulus_Kurtulus_Zeynep_HW6_player.hpp
//  zeynepkurtulus_Kurtulus_Zeynep_HW6
//
//  Created by Zeynep Kurtulus on 15.05.2022.
//

#ifndef zeynepkurtulus_Kurtulus_Zeynep_HW6_player_h
#define zeynepkurtulus_Kurtulus_Zeynep_HW6_player_h

#include <string>
#include <iostream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_board.h"
using namespace std;

template <class type> // templated class now the type is playertype
class Player
{
private:
    Board<type> & myboard; // players will share the same board matrix so it is given with referrence parameter
    static int next_id; // like a prototype declaration
    int current_id;
public:
    
    
    Player(Board<type> &boardmatrix); // parametric constructor
    bool updateCell(int row, int col, const type &value);
    void updateMyCells(int updatevalue);
    bool unclaimOwnership(int row, int col); // unclaims the ownership if it is currently owned by that player.
    void unclaimOwnerships(); // unclaims the ownership of all the cells owned by that (caller) player object.
};
template <class type>
int Player<type>::next_id = 1; // definition and initialization



#endif /* zeynepkurtulus_Kurtulus_Zeynep_HW6_player_h */
