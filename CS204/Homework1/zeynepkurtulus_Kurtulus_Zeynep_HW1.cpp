#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW1_strutils.h"
#include <sstream>
#include <iomanip>
using namespace std;

struct cell
{
    char letter;
    char color;
};

bool openfile(string filename){ //checks if the file can be opened
    bool validator = true;
    ifstream input;
    input.open(filename.c_str());
    if (input.fail())
    {
        validator = false;
    }
    return validator;
}

bool lencheck(string & userguess, unsigned long int wordlen){ // checks the number of letters in the string
    bool validator = false;
    unsigned long int userlen = userguess.length();
    if (userlen == wordlen) {
        validator = true;
    }
    
    while(validator == false){
        validator = true;
        while (userlen > wordlen) //invalid
        {
            validator = false;
            cout << "The word is too long!" << endl;
            cout << "What's your guess? ";
            cin >> userguess;
            userlen = userguess.length();
            if (userlen == wordlen) {
                validator = true;
            }
            
        }
        while (userlen < wordlen)
        {
            validator = false;
            cout << "The word is too short!" << endl;
            cout << "What is your guess? ";
            cin >> userguess;
            userlen = userguess.length();
            if (userlen == wordlen) {
                validator = true;
            }
        }
    }
    return validator;
}

void initialize(vector<vector<cell>> & mtrx, unsigned long int rows, unsigned long int cols){ // initializes all cells of the matrix to '-'
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mtrx[i][j].color = '-';
            mtrx[i][j].letter = '-';
        }
    }
    
}

bool lowercase(string userin){ // checks whether the string is lowercase
    bool v1 = true;
    unsigned long int l = userin.length();
    string s;
    for (int i = 0; i < l; i++) {
        if ( 'a' <= userin[i] && userin[i] <= 'z' && v1 == true) {
            v1 = true;
        }
        else
            v1 = false;
    }
    return v1;
}

bool duplicate(string s){ // checks whether there are repeated letters
    bool v2 = true;
    unsigned long int a = s.length();
    for (int i = 0; i < a - 1; i++) {
        for (int k = i + 1; k < a ; k++) {
            if (s.at(i) == s.at(k)) {
                v2 = false;
            }
        }
    }
    return v2;
}

bool previouswords(const vector<string> & wordstorage, string userword){ // checks whether the word is previously entered by the user
    bool v3 = true;
    int counter = 0;
    for (int i = 0; i < wordstorage.size(); i++) {
        if (wordstorage[i] == userword && v3 == true) {
            counter++;
            if (counter > 1) {
                v3 = false;
            }
            
        }
    }
    
    return v3;
}


void edit(vector<vector<cell>> & mat, string usergs, int attemptcnt, string wrd){ // fills in the matrix
    for (int i = 0; i < usergs.length(); i++)
    {
        if (usergs.at(i) == wrd.at(i) )
        {
            mat[attemptcnt - 1][i].letter = usergs[i];
            mat[attemptcnt - 1][i].color = 'G';
        }
        else if (wrd.find(usergs[i]) != string::npos)
        {
            mat[attemptcnt - 1][i].letter = usergs[i];
            mat[attemptcnt - 1][i].color = 'Y';
        }
        else
        {
            mat[attemptcnt - 1][i].letter = usergs[i];
            mat[attemptcnt - 1][i].color = 'B';
        }
    }
}

void display(const vector<vector<cell>> & mat, int atmpt, int rw, int cl){ // prints the matrix
    
    for (int i = 0; i < rw; i++) {
        for (int k = 0; k < cl; k++) {
            cout << "|| " << mat[i][k].letter << " , " <<  mat[i][k].color << " ";
        }
        cout << "|| " << endl;
    }
}

bool greenletter(string guess, const vector<vector<cell>> & matrix, int attmptcnt){ // checks for the places of the green letters
    bool v7 = true;
    
    for (int i = 0; i < guess.length(); i++) {
        if (matrix[attmptcnt - 1][i].color == 'G' && (guess.at(i) != matrix[attmptcnt - 1 ][i].letter)) {
            v7 = false;
        }
    }
    return v7;
}

bool inputchecker(vector<string> & stor, string & guess, unsigned long int len, vector<vector<cell>> & mat, int attempcn){ // checks all the input checks
    bool v6 = false;
    if (lencheck(guess, len) && previouswords(stor, guess) && duplicate(guess) && lowercase(guess) && greenletter(guess, mat, attempcn)) {
        v6 = true;
    }
    return v6;
}
    
int main(){
    bool validator = false;
    vector<string> wordstorage {}; // an empty vector to store the words tried by the user
    ifstream input;
    int attemptstorage = 0, rows, counter = 1, attemptcount = 0;
    unsigned long int len = 0;
    unsigned long int cols = 0;
    cout << "Welcome to SWordle!" << endl;
    string filename, attempt, word, line1, userguess;
    cout << "Please enter the filename: ";
    cin >> filename;
    while (! openfile(filename)) //file does not exist
    {
        cout << "Couldn't find the file!" << endl;
        cout << "Please enter the filename: ";
        cin >> filename;
    }
    input.open(filename.c_str());
    while (getline(input, line1)) {
        istringstream iss1(line1);
        if (counter == 1) { // first line is the number of attempts
            counter ++;
            iss1 >> attempt;
            attemptstorage = atoi(attempt);
            
        }
        else if (counter > 1){ // second line is the word
            iss1 >> word;
        }
    }
    len = word.length(); // length of the word
    cout << "The word that you will guess has " << len << " letters and you have " << attempt << " attempts." << endl;
    rows = attemptstorage;
    cols = len;
    vector<vector<cell>> mymat(rows, vector<cell>(cols)); // matrix of the struct "cell" 
    initialize(mymat, rows, cols);
    cout << "What's your guess? ";
    cin >> userguess;
    lencheck(userguess, len); // 1st check
    
    while (lowercase(userguess) == false) { // 2nd check
        cout << "Your input has illegal letters!" << endl;
        cout << "What's your guess? ";
        cin >> userguess;
        wordstorage.push_back(userguess);
    }
    while (duplicate(userguess) == false) { // 3rd check
        cout << "Your input has a duplicate letter!" << endl;
        cout << "What's your guess? ";
        cin >> userguess;
        //wordstorage.push_back(userguess);
    }
    while (previouswords(wordstorage, userguess) == false) { // 4th check
        cout << "You have already tried this word!" << endl;
        cout << "What's your guess? ";
        cin >> userguess;
        //wordstorage.push_back(userguess);
    }
    
    // if the guessed word passes all the input checks
    
    while (lencheck(userguess, len) && lowercase(userguess) && duplicate(userguess) && previouswords(wordstorage, userguess )&& attemptcount < attemptstorage && validator == false) // if all the input checks  are true and the number of attempts are not exceeded
    {
        attemptcount++; // increment the attempy count if the input is valid 
        wordstorage.push_back(userguess); // store the word in the vector
        if ((attemptcount > attemptstorage ) && (userguess != word))
        {
            edit(mymat, userguess, attemptcount, word);
            display(mymat, attemptcount, rows, cols);
            cout << "You lose!";
            validator = true;
        }
        else if ((attemptcount <= attemptstorage) && (userguess == word))
        {
            edit(mymat, userguess, attemptcount, word);
            display(mymat, attemptcount, rows, cols);
            cout << "You win!";
            validator = true;
        }
        else if ((attemptcount == attemptstorage) && (userguess != word)){
            edit(mymat, userguess, attemptcount, word);
            display(mymat, attemptcount, rows, cols);
            cout << "You lose!";
            validator = true;
        }
        if (validator == false) {
            
            edit(mymat, userguess, attemptcount, word);
            
            display(mymat, attemptcount, rows, cols);
            
            cout << "What's your guess? ";
            cin >> userguess;
            wordstorage.push_back(userguess);
            while (inputchecker(wordstorage, userguess, len, mymat, attemptcount) == false) { // if it fails either of the input checks
                lencheck(userguess, len); // 1st check
                while (lowercase(userguess) == false && lencheck(userguess, len)) { // 2nd check
                    cout << "Your input has illegal letters!" << endl;
                    cout << "What's your guess? ";
                    cin >> userguess;
                    wordstorage.push_back(userguess);
                }
                while (duplicate(userguess) == false && lencheck(userguess, len) && lowercase(userguess)) { // 3rd check
                    cout << "Your input has a duplicate letter!" << endl;
                    cout << "What's your guess? ";
                    cin >> userguess;
                    wordstorage.push_back(userguess);
                }
                while (greenletter(userguess, mymat, attemptcount) == false && lowercase(userguess)&&  duplicate(userguess) && lowercase(userguess)) { // 5th check
                    cout << "You did not use the green letter in your word!" << endl;
                    cout << "What's your guess? ";
                    cin >> userguess;
                    wordstorage.push_back(userguess);
                }
                while (previouswords(wordstorage, userguess) == false && lowercase(userguess) && duplicate(userguess) && lowercase(userguess) && greenletter(userguess, mymat, attemptcount)) { // 4th check
                    cout << "You've already tried this word!" << endl;
                    cout << "What's your guess? ";
                    cin >> userguess;
                    wordstorage.push_back(userguess);
                }
                
            }
        }
    }
    
    cout << endl;
        return 0;
}
