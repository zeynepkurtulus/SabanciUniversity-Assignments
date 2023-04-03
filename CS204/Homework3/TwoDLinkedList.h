
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct node
{
    char data;
    node *right;
    node *down;
    node() // default constructor
    {}
    node(char &ch, node *r, node*d)  // constructor
    {
        data = ch;
        right = r;
        down = d;
    }
};


class TwoDLinkedList{
private:
    node *head;
    
public:
    TwoDLinkedList(); // constructor 
    void add_row_sorted(string str);
    void displayFullMatrix();
    void displayFullMatrixReversed();
    void display_rows_starting_with(char ch);
    void display_cols_starting_with(char ch);
    int delete_rows_starting_with(char ch);
    int delete_cols_starting_with(char ch);
    void clear();
};
