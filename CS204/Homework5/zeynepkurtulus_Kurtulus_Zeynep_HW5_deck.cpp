//
//  zeynepkurtulus_Kurtulus_Zeynep_HW5.cpp
//  zeynepkurtulus_Kurtulus_Zeynep_HW5
//
//  Created by Zeynep Kurtulus on 25.04.2022.
//

#include "zeynepkurtulus_Kurtulus_Zeynep_HW5_deck.h"
#include <iostream>

Deck::Deck() //default constructor
{
    size = 0;
    cardarr = NULL;
}

Deck::Deck(const int num){ // generates a new deck
    size = num;
    cardarr = new Card[num];
}

Card * Deck::getarr() const{ // accessor for dynamic array
    return cardarr;
}

int Deck::findname(const Card&rhs) const // if it finds the name it returns the index of it otherwise it will return -2
{
    for (int i = 0; i < size; i++) {
        if (cardarr[i].name == rhs.name) {
            return i;
        }
        
    }
    return -2;
}

int Deck::findenergy(const Card &rhs) const // if it finds the energy it returns the index of it otherwise it will return -2
{
    for (int i = 0; i < size; i++) {
        if (cardarr[i].energy == rhs.energy) {
            return i;
        }
    }
    return -2;
}

Deck::~Deck(){ // destructor removes the elements of the dynamic array
    size = 0;
    delete [] cardarr;
}



int Deck::getsize() const{ // size helper function
   return this->size;
}

Deck::Deck(const Deck& copy){ // deep copy constructor
    size = copy.size; // copies the size of the array
    
    cardarr = new Card[size]; // generates a new array
    for (int j = 0; j < size; j++) {
        cardarr[j] = copy.cardarr[j]; // fills in the array
    }
}

ostream &Deck::printhelper(ostream &os) const { // helper function, it has acces to private data members
    for (int i = 0; i < size ; i++) {
        Card c = cardarr[i];
        os << i +1 << ": " << c.name << " - " << c.energy << endl;
    }
    return os;
}

Deck Deck::operator+(const Card& rhs) // adds a card at the bottom of the newly created deck object.
{
    Deck newdeck;
    int updatedsize = this->size + 1;
    Card *newcard = new Card[updatedsize]; // newly created Card array
    for (int i = 0; i < this->size; i++) {
        newcard[i] = this->cardarr[i];
    }
    newcard[this->size] = rhs;
    newdeck.addcards(newcard, updatedsize);
    return newdeck;
}

Deck operator+(const Deck& lhs, const Deck& rhs) // + operator overloading function for concatenation of two Deck obj.
{
    int idx = 0;
    Deck newdeck; // new deck object that will be returned
    Card *rhsarr = rhs.getarr();
    Card *lhsarr = lhs.getarr();
    int updatedsize = lhs.getsize() + rhs.getsize(); // new size
    Card *newcard = new Card[updatedsize]; // new dynamic memory allocation for the dynamic array
    for (int i = 0; i < lhs.getsize(); i++) // add the elements of the first deck
    {
        newcard[i] = lhsarr[i];
    }
    for (int k = lhs.getsize(); k < updatedsize; k++) // add the elements of the second deck
    {
        newcard[k] = rhsarr[idx];
        idx++;
    }
    newdeck.addcards(newcard, updatedsize); // assign the cards to the newly created deck obj.
    return newdeck; // return the newly created deck obj.
}

ostream& operator<<(ostream& os, const Deck& dc) // << operator overloading function
{
    return dc.printhelper(os);
}

Deck& Deck::operator+=(const Deck&rhs){ // adds to decks together, top is the lhs bottom is the rhs
    int modifsize = this->size + rhs.size;
    int idx = 0;
    Card *lhscard = this->cardarr;
    Card *rhscard = rhs.getarr();
    Card *newcard = new Card[modifsize];
    Deck newdeck;
    for (int i = 0; i < size; i++) { // assign the contents of the lhs into a newly created deck
        newcard[i] = lhscard[i];
    }
    //this->size = 0; // in order to modeify the lhs
    //delete [] this->cardarr; // in order to modify the lhs we have to delete it first
    for (int k = size; k <modifsize ; k++) { // assignt the contents of the rhs into a newly created deck
        newcard[k] = rhscard[idx];
        idx++;
    }
    newdeck.addcards(newcard, modifsize);
    this->size = modifsize; // update the size of the lhs according to the new size
    delete [] this->cardarr;
    this->cardarr = new Card[modifsize];
    for (int j = 0; j < modifsize; j++) { // assign the contents of the newly created deck into to lhs in order to return lhs
        this->cardarr[j] = newdeck.cardarr[j];
    }
    
    return *this; // return the lhs
}

bool Deck::operator==(const Deck&rhs) const // checks if two decks have the same energy
{
    int lhsen = 0;
    int rhsen = 0;
    for (int i = 0; i < size; i++) {
        lhsen += this->cardarr[i].energy; // total energy of the lhs
    }
    for (int k = 0; k < rhs.size; k++) {
        rhsen += rhs.cardarr[k].energy; // total energy of the rhs
    }
    if (rhsen == lhsen) { // checks whether they have the same energy
        return true; // if yes return true
    }
    else
        return false; // else return false 
}

Card& Deck::operator[](const int idx) const // overloading of [] operator, returns the index of the rhs th index in the deck 
{
    return this->cardarr[idx]; // return the idx th index of the cardarr
    
}

Deck& Deck::operator=(const Deck& rhs){
    
    if (this != &rhs) {  // if lhs is not the same as the rhs
        delete []this->cardarr;
        this->size = 0;
        size = rhs.size;
        cardarr = new Card[size];

        for (int i = 0; i < size; i++) {
            cardarr[i] = rhs.cardarr[i];
        }
    }
    return *this; // return the pointer to the newly created array
}

const bool operator<=(const Card& lhs, const Deck& rhs) // <= operator
{
    if ((rhs.findname(lhs) != -2) && (rhs.findenergy(lhs) != -2)) {
        return true;
    }
    else
        return false;
}

void Deck::addcards(Card* &c, const int num) // adds cards to the newly created deck
{
    this->cardarr = c; // cardarr of newdeck
    this->size = num; // size of newdeck
}



Deck Deck::operator-(const int rhs) // return a new deck obj. with top rhs elements removed
{
    Deck newdeck;
    int numofcards = this->size;
    int newsize = numofcards - rhs;
    if ((rhs > numofcards) || (rhs == numofcards) || (numofcards == 0)) { // return an empty deck
        return newdeck; // empty deck since it is created with default constructor
    }
    else
    {
        Card *arr = new Card[newsize]; // new dynamically allocated card
        for (int i = 0; i < numofcards; i++) {
            arr[i] = this->cardarr[i + rhs]; // assign the lhs to the newly allocated card
        }
        //this->size = 0;
        //delete [] cardarr; // free the memory to avoid leak
        newdeck.addcards(arr, newsize); // assignt the cards to the deck
        return newdeck;
    }
}



const bool operator>(const Deck & lhs, const int rhs)   // checks if the lhs has more than rhs cards; returns false otherwise.
{
    int cardnum = lhs.getsize();
    if (cardnum > rhs) {
        return true;
    }
    else
        return false;
}


const bool operator<(const Deck&lhs, const Deck&rhs) // checks if the deck lhs has more energy than rhs cards
{
    int leften = 0;
    int righten = 0;
    Card *lhsarrhold = lhs.getarr();
    Card *rhsarrhol = rhs.getarr();
    int lhsize = lhs.getsize();
    int rhsize = rhs.getsize();
    for (int i = 0; i < lhsize ; i++) {
        leften += lhsarrhold[i].energy;
    }
    for (int k = 0; k < rhsize; k++) {
        righten += rhsarrhol[k].energy;
    }
    if (leften < righten) {
        return true;
    }
    else
        return false;
}




