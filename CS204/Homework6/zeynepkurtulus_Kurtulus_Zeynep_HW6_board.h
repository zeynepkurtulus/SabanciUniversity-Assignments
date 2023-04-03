//
//  zeynepkurtulus_Kurtulus_Zeynep_HW6_board.h
//  zeynepkurtulus_Kurtulus_Zeynep_HW6
//
//  Created by Zeynep Kurtulus on 15.05.2022.
//

#ifndef zeynepkurtulus_Kurtulus_Zeynep_HW6_board_h
#define zeynepkurtulus_Kurtulus_Zeynep_HW6_board_h
#include <string>
#include <iostream>

using namespace std;

template <class type>
struct Cell
{
    type value; // value has no certain type, it is either int or char
    int owner; // owner is of type int
};

template <class type>
class Board {
private:
    int rows, cols;
    Cell<type> **mymat; // pointer to pointer of type boardtype
public:
    Board(int rows, int cols); // parametric constructor
    Board(const Board &); // deep copy constructor
    ~Board(); // destructor
    void displayBoard(); // displays the content of the board
    void updateBoardCells(int id, type val); // populate all the cells owned by that player the given value.
    int knowTheOwner(int row, int col); // returns the owner of the cell
    int getPlayerCellsCount(int id); // returns number of cells that player owns
    int getrows();
    int getcols();
    int getid(int row, int col); // helper function
    type getvalue(int row, int col); // helper function
    Board<type> &updatehelper(int row, int col, const type updtval);
    Board<type> & ownerhelper(int row, int col, int owner);
};

#endif /* zeynepkurtulus_Kurtulus_Zeynep_HW6_board_h */
