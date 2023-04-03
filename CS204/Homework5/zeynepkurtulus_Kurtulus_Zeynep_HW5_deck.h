//
//  zeynepkurtulus_Kurtulus_Zeynep_HW5.h
//  zeynepkurtulus_Kurtulus_Zeynep_HW5
//
//  Created by Zeynep Kurtulus on 25.04.2022.
//
#include <string>
#include <iostream>
using namespace std;
#ifndef zeynepkurtulus_Kurtulus_Zeynep_HW5_deck_h
#define zeynepkurtulus_Kurtulus_Zeynep_HW5_deck_h

struct Card //struct
{
    string name;
    int energy;
    Card() // default constructor
    {}
    Card(string &str, int &num)
    {
        name = str;
        energy = num;
    }
    
};

class Deck {
private:
    int size; // size of the array: number of cards inside the deck object 
    Card *cardarr; // card pointer
    
public:
    Deck(); // default constructor >> it is called eveytime we create a deck object
    ~Deck(); // destructor >> runs each time a liftime of an object is ended
    Deck (const Deck&); //copy constructor >> it is called when an object initializes another object or when an object is return from a function by value or when an object is passed by value to a function (it will copy the deck object i.e. the dynamic array)
    int getsize() const; // accessor for the size
    ostream &printhelper(ostream &os) const; // member function to help the << operator overloading to access private data members
    Card* getarr() const; // accessor for the dynamic array
    Deck(const int num); // for creating a new Deck 
    Deck operator+(const Card & rhs); // + operator overloading: it adds card to the deck of cards
    Deck operator-(const int rhs); // - operator overloading: it removes card from the deck of cards
    Deck & operator= (const Deck & rhs);
    Deck & operator+= (const Deck &rhs); // += operator overloading: it will add two deck objects
    bool operator==(const Deck& rhs) const; // == operator overloading: checks if two decks have the same energy
    int findname(const Card&rhs) const; // helper function
    int findenergy(const Card& rhs) const; // helper function
    void addcards(Card* &card, const int num); // add cards to the newly created deck 
    Card& operator[](const int idx) const; // return reference to the rhs th index of the deck
    
    
};

// free function declarations 

ostream& operator<<(ostream& os, const Deck& dc); // << operator overloading: for cout << statements 
const bool operator<=(const Card& lhs, const Deck& rhs); // <= operator overloading: checks if the card of the left-hand side Card element exists
Deck operator+(const Deck& lhs, const Deck& rhs); // + operator overloading: the concatenation of two Deck operands
const bool operator>(const Deck& lhs, const int rhs); // > operator overloading: check if the lhs deck has less total energy than the rhs deck.
const bool operator<(const Deck&lhs, const Deck&rhs); // < operator overloading: checks if the deck lhs has more than rhs cards




#endif
