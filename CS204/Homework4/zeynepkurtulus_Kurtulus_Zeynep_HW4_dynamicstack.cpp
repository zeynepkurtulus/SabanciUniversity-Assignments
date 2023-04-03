 //Do not forget to rename this file according to the file naming rules
#include <iostream>
#include "DynStackHW4.h"
using namespace std;

//************************************************
// Constructor to generate an empty stack.       *
//************************************************
DynStack::DynStack()
{
	top = NULL; 
}

//************************************************
// Member function push pushes the argument onto *
// the stack.                                    *
//************************************************
void DynStack::push(char symbol, int line_number)
{
	StackNode *newNode;

	// Allocate a new node & store Num
	newNode = new StackNode;
	newNode->symbol = symbol;
	newNode->line_number = line_number;

	// If there are no nodes in the list
	// make newNode the first node
	if (isEmpty())
	{
		top = newNode;
		newNode->next = NULL;
	}
	else	// Otherwise, insert NewNode before top
	{
		newNode->next = top;
		top = newNode;
	}
}

//****************************************************
// Member function to delete all the nodes in the    *
// stack                                             *
//****************************************************
void DynStack::clear(){
	StackNode * temp = top; 
	while (top!=nullptr){
		top = top->next;
		delete temp;
		temp = top;
	}
	top = nullptr;
}

//****************************************************
// Destructor to delete the elements in the stack.   *
//****************************************************
DynStack::~DynStack(){
	this->clear();
}

//************************************************
// Copy constructor to copy the stack `rhs` into *
// the current stack.                            *
//************************************************
DynStack::DynStack(const DynStack& rhs){
	top = rhs.clone();
}

//************************************************
// Create a clone of the StackNodes of the       *
// calling object and return a pointer to the    *
// first one.
//************************************************
StackNode* DynStack::clone() const{
	 if (top == nullptr){
		 return nullptr;
	 } else {
		StackNode * existing_list_ptr = top;
		StackNode * new_list_ptr = new StackNode;
		new_list_ptr->line_number = existing_list_ptr->line_number;
		new_list_ptr->symbol = existing_list_ptr->symbol;
		new_list_ptr->next = nullptr;
		StackNode* ptr = new_list_ptr;
		while(existing_list_ptr->next!=nullptr){
			ptr->next = new StackNode;
			ptr=ptr->next;
			existing_list_ptr = existing_list_ptr->next;
			ptr->symbol = existing_list_ptr->symbol;
			ptr->line_number = existing_list_ptr->line_number;
		}
		return new_list_ptr;
	 }
}

//************************************************
// Assignment operator to copy the stack `rhs`   *
// into the current stack.                       *
//************************************************
const DynStack& DynStack::operator=(const DynStack& rhs){
	if (&rhs == this){
		return *this;
	}
	this->clear();
	top = rhs.clone();
	return *this;
}
//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************
void DynStack::pop(char& symbol, int &line_number)
{
	StackNode *temp;

	if (isEmpty())
	{
		cout << "Attempted to pop from an empty stack. Program terminates. If you got this message, then there is a problem in your program." << endl;
		exit(1);
	}
	else	// pop value off top of stack
	{
		symbol = top->symbol;
		line_number = top->line_number;
		temp = top->next;
		delete top;
		top = temp;
	}
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************
bool DynStack::isEmpty(void)
{
	bool status;

	if (top == NULL)
		status = true;
	else
		status = false;

	return status;
}

