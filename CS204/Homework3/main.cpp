# include <iostream>
# include <string>
# include <fstream>
#include "TwoDLinkedList.h"


using namespace std;

int main()
{
    TwoDLinkedList list;
    string fileName;
    ifstream myfile;
	do
    {
        cout << "Please enter the file name: ";
        cin >> fileName;
        myfile.open(fileName);
    } while (myfile.fail());
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
    string line;
    string s;
	while (getline(myfile, line))
    {
        s = line;
        list.add_row_sorted(s);
    }
    myfile.close();

	cout<< "\nPlease enter the number of the option from the list below:"<<endl;
	cout<<"1. Display the full matrix"<<endl;
    cout<<"2. Display the full matrix in reverse order"<<endl;
    cout<<"3. Display all the rows starting with a specific character"<<endl;
    cout<<"4. Display all the columns starting with a specific character"<<endl;
    cout<<"5. Delete all the rows starting with a specific character"<<endl;
	cout<<"6. Delete all the columns starting with a specific character"<<endl;
    cout<<"7. Clear the data structure and exit\n"<<endl;
	
	char option;
	cout<<"Please enter a menu option: ";
    cin>>option;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');  // add it wherever needed to ignore all the extra input.

	while (option!='7')
    {
        if (option=='1')
        {
			cout<<endl;
            list.displayFullMatrix();
        }
        else if (option=='2')
        {
			cout<<endl;
            list.displayFullMatrixReversed();
        }
        else if (option=='3')
        {
            char c;
            cout<<"Please enter first character of the rows to display: ";
            cin>>c;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout<<endl;
            list.display_rows_starting_with(c);
        }
        else if (option=='4')
        {
            char c;
            cout<<"Please enter first character of the columns to display: ";
            cin>>c;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout<<endl;
            list.display_cols_starting_with(c);
        }
        else if (option=='5')
        {
            char c;
            cout<<"Please enter first character of the rows to delete: ";
            cin>>c;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			int number_of_deleted_rows;
            number_of_deleted_rows = list.delete_rows_starting_with(c);
			cout <<"The number of deleted rows is: " <<number_of_deleted_rows<< endl;
        }
        else if (option=='6')
        {
            char c;
            cout<<"Please enter first character of the columns to delete: ";
            cin>>c;
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			int number_of_deleted_columns;
            number_of_deleted_columns = list.delete_cols_starting_with(c);
			cout <<"The number of deleted columns is: " <<number_of_deleted_columns<< endl;
        }
        else
        {
            cout<<"\nInvalid input. You need to enter a valid menu option."<<endl;  
        }

        cout<<"\nPlease enter a menu option: ";
		cin>>option;
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
	list.clear();
	cout<< "Clearing the data structure and exiting the program..."<<endl;

	cin.get();
	cin.ignore();
    return 0;
}
