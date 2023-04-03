#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_board.h" //change this with your board header file name
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_player.h" //change this with your player header file name
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_board.cpp"
#include "zeynepkurtulus_Kurtulus_Zeynep_HW6_player.cpp"

using namespace std;

//displays board content and players' cell counts
template <class T>
void display (Board<T> b) //we made this parameter value parameter on purpose :)
{
	b.displayBoard();
	cout<< "The numbers of the owned cells by the two players are: " <<endl;
	cout<< "Player1: "<< b.getPlayerCellsCount(1) <<"\t"<< "Player2: "<< b.getPlayerCellsCount(2)<< endl;
	cout<<endl;
}


int main()
{
	string fileName;
	ifstream myfile;
	do
    {
        cout << "Please enter the file name: ";
        cin >> fileName;
        myfile.open(fileName);
    } while (myfile.fail());
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 

	string line, type, size;
    string command;
	int rows, cols;

	getline(myfile, type); // read the first line of the file (contains the data type char of the values). 
	getline(myfile, size); // read the second line of the file (contains the number of rows and columns of the board). 

	stringstream ss1, ss2;  
	ss1 << size;
	ss1 >> rows;  ss1 >> cols;

	int i, j, playerID;
	bool r;

	if (type[0]=='c') // char 
	{ 
		char value;
		Board<char> b (rows,cols);  //char board
		b.updateBoardCells(0, '-'); // initial values of the cells' contents are set here. All to be '-'

		Player<char> player1 (b);
		Player<char> player2 (b);
		
		while (getline(myfile, line))
		{
			ss2<<line;
			ss2>>command;
			if (command == "uc") // update cell
			{
				ss2>>playerID; ss2>>i; ss2>>j; ss2>>value;
				if (playerID == 1 && (i>=0 && i<rows) && (j>=0 && j<cols)) // check rang and valid argument
				{
					r = player1.updateCell(i,j,value);
					if (!r)
						cout<<"Error! You cannot update other player's cells."<<endl; 
					else 
						cout<<"Updated ("<< i<<","<<j <<") cell by player "<<playerID<<" with value "<<value<<endl;
				}
				else if (playerID == 2 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player2.updateCell(i,j,value);
					if (!r)
						cout<<"Error! You cannot update other player's cells."<<endl;
                    else
                        cout<<"Updated ("<< i<<","<<j <<") cell by player "<<playerID<<" with value "<<value<<endl;
        
                    
				}
				else 
					cout<< "Invalid arguments!"<<endl;
			}

			else if (command == "d") // display board
			{
				display(b);
			}

			else if (command == "ucs") // update cells
			{
				ss2>>playerID;
				ss2>>value;
				if (playerID == 1)
				{
					player1.updateMyCells(value);
					cout<<"Updated all cells of player "<<playerID<<" with value "<<value<<endl;
				}
				else if (playerID == 2)
				{
					player2.updateMyCells(value);
					cout<<"Updated all cells of player "<<playerID<<" with value "<<value<<endl;
				}
				else 
				{
					cout<< "Error! Wrong Player ID"<<endl;
				}
			}
			
			else if (command == "unc") // unclaim cell
			{
				ss2>> playerID; ss2>> i; ss2 >> j;
				if (playerID == 1 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player1.unclaimOwnership(i, j);
					if (!r)
						cout<<"Error! You can only unclaim one of your cells."<<endl;
					else
						cout<< "Player "<<playerID<<" has unclaimed his/her ("<< i<<","<<j <<") cell"<<endl;
				}
				else if (playerID == 2 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player2.unclaimOwnership(i, j);
					if (!r)
						cout<<"Error! You can only unclaim one of your cells."<<endl;
					else
						cout<< "Player "<<playerID<<" has unclaimed his/her ("<< i<<","<<j <<") cell"<<endl;
				}
				else
					cout<< "Invalid arguments!"<<endl;
			}

			else if (command == "uncs") // unclaim cells
			{
				ss2>> playerID;
				if (playerID == 1)
				{
					player1.unclaimOwnerships();
					cout<< "Player "<<playerID<<" has unclaimed all of their cells"<<endl;
				}
				else if (playerID == 2)
				{
					player2.unclaimOwnerships();
					cout<< "Player "<<playerID<<" has unclaimed all of their cells"<<endl;
				}
				else 
					cout<<"Error! Wrong Player ID"<<endl;			
			}

			else if (command == "ko") // know owner
			{
				ss2>>i; ss2>>j;
				if ((i>=0 && i<rows) && (j>=0 && j<cols))
					cout << "The owner of the cell is player: " << b.knowTheOwner(i, j) << endl;
				else 
					cout<< "Invalid arguments!"<<endl; 
			}

		ss2.clear(); //  clear the error state of the stream
		ss2.str(std::string()); // clear the content of the string stream
		}
	}

	else if (type[0]=='i') // integer 
	{ 
		int value;
		Board<int> b (rows,cols);  //Integer Board
		b.updateBoardCells(0, -1); // initial values of the cells' contents are set here. All to be -1
		Player<int> player1 (b);
		Player<int> player2 (b);
		
		while (getline(myfile, line))
		{
			ss2<<line;
			ss2>>command;
			if (command == "uc") // update cell
			{
				ss2>>playerID; ss2>>i; ss2>>j; ss2>>value;
				if (playerID == 1 && (i>=0 && i<rows) && (j>=0 && j<cols)) 
				{
					r = player1.updateCell(i,j,value);
					if (!r)
						cout<<"Error! You cannot update other player's cells."<<endl; 
					else 
						cout<<"Updated ("<< i<<","<<j <<") cell by player "<<playerID<<" with value "<<value<<endl;
				}
				else if (playerID == 2 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player2.updateCell(i,j,value);
					if (!r)
						cout<<"Error! You cannot update other player's cells."<<endl;
					else
						cout<<"Updated ("<< i<<","<<j <<") cell by player "<<playerID<<" with value "<<value<<endl;
				}
				else 
					cout<< "Invalid arguments!"<<endl;
			}

			else if (command == "d") // display board
			{
				display(b);
			}

			else if (command == "ucs") // update cells
			{
				ss2>>playerID;
				ss2>>value;
				if (playerID == 1)
				{
					player1.updateMyCells(value);
					cout<<"Updated all cells of player "<<playerID<<" with value "<<value<<endl;
				}
				else if (playerID == 2)
				{
					player2.updateMyCells(value);
					cout<<"Updated all cells of player "<<playerID<<" with value "<<value<<endl;
				}
				else 
				{
					cout<< "Error! Wrong Player ID"<<endl;
				}
			}
			
			else if (command == "unc") // unclaim cell
			{
				ss2>> playerID; ss2>> i; ss2 >> j;
				if (playerID == 1 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player1.unclaimOwnership(i, j);
					if (!r)
						cout<<"Error! You can only unclaim one of your cells."<<endl;
					else
						cout<< "Player "<<playerID<<" has unclaimed his/her ("<< i<<","<<j <<") cell"<<endl;
				}
				else if (playerID == 2 && (i>=0 && i<rows) && (j>=0 && j<cols) )
				{
					r = player2.unclaimOwnership(i, j);
					if (!r)
						cout<<"Error! You can only unclaim one of your cells."<<endl;
					else
						cout<< "Player "<<playerID<<" has unclaimed his/her ("<< i<<","<<j <<") cell"<<endl;
				}
				else
					cout<< "Invalid arguments!"<<endl;
			}

			else if (command == "uncs") // unclaim cells
			{
				ss2>> playerID;
				if (playerID == 1)
				{
					player1.unclaimOwnerships();
					cout<< "Player "<<playerID<<" has unclaimed all of their cells"<<endl;
				}
				else if (playerID == 2)
				{
					player2.unclaimOwnerships();
					cout<< "Player "<<playerID<<" has unclaimed all of their cells"<<endl;
				}
				else 
					cout<<"Error! Wrong Player ID"<<endl;			
			}

			else if (command == "ko") // know owner
			{
				ss2>>i; ss2>>j;
				if ((i>=0 && i<rows) && (j>=0 && j<cols))
					cout << "The owner of the cell is player: " << b.knowTheOwner(i, j) << endl;
				else 
					cout<< "Invalid arguments!"<<endl; 
			}

		ss2.clear(); //  clear the error state of the stream
		ss2.str(std::string()); // clear the content of the string stream
		}
	}

    myfile.close();
	cout<< "Deallocating memory and ending program..."<<endl;

	cin.get();
	cin.ignore();
	return 0;
}


// sample runs to indicate error messages 
