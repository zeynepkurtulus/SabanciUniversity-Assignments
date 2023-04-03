#include <iostream>
#include <fstream>
#include "zeynepkurtulus_Kurtulus_Zeynep_HW5_deck.h"  //replace this header file name with yours
using namespace std;

// Count the number of cards in a deck
int count_cards(const Deck& deck){
    int card_count = 0;
    // card_count will keep incrementing as long as
    // deck has more cards than card_count
    while (deck > card_count) card_count++;
    return card_count;
}

// Read a deck from an input file stream
Deck read_deck(ifstream & fin){
    string name;
    int energy;
    Deck new_deck;
    int i = 0;
    while (fin >> name >> energy){
        Card c;
        c.name = name;
        c.energy = energy; 
        new_deck = new_deck + c;
    }
    return new_deck;
}

// Play a game with decks d1 and d2
// Winner gets the cards of both decks
Deck play_game(Deck d1, Deck d2){
    Deck discard_pile; // Cards that lose are placed here
    Deck winning_deck; // Reward for the winner
    // While both decks still have cards 
    while (d1 > 0 && d2 > 0){
        // Get the top card in d1
        Card player_1_card = d1[0];
        // Remove one card from the top of d1
        // i.e., remove the card player_1_card
        d1 = d1-1;
        // Get the top card in d2
        Card player_2_card = d2[0];
        // Remove one card from the top of d2
        // i.e., remove the card player_2_card
        d2 = d2-1;
        cout << "P1: " << player_1_card.name <<" @ " << player_1_card.energy << " Vs. " << " P2: " << player_2_card.name <<" @ " << player_2_card.energy << endl;
        if (player_1_card.energy > player_2_card.energy){
            cout << "Player 1 wins the round\n";
            // Place the card player_1_card in the bottom of d1
            d1 = d1+player_1_card; 
            // Add the lost card to the discard_pile deck
            discard_pile = discard_pile+player_2_card;
        } else if (player_1_card.energy < player_2_card.energy){
            cout << "Player 2 wins the round\n";
            // Place the card player_2_card in the bottom of d2
            d2 = d2+player_2_card; 
            // Add the lost card to the discard_pile deck
            discard_pile = discard_pile+player_1_card;
        } else {
            // Both players lose their cards
            cout << "Players tied this round\n";
            // Place player_1_card and player_2_card in the discard_pile deck
            discard_pile = discard_pile+player_1_card;
            discard_pile = discard_pile+player_2_card;
        }
    }
    // If d1 still has cards, then player 1 wins
    if (d1 > 0){
        cout << "Player 1 wins the game!\n";
        // Combine the cards in the discard_pile deck and in d1 
        // to create the winning_deck that the winner gets ex1_d2.txt
        winning_deck=discard_pile+d1;
    } else if (d2 > 0){
        cout << "Player 2 wins the game!\n";
        // Combine the cards in the discard_pile deck and in d2 
        // to create the winning_deck that the winner gets 
        winning_deck=discard_pile+d2;
    } else {
        cout << "Game ended with a tie!\n";
    }
    return winning_deck;
}

// Counts the number of unique cards in `deck` 
int count_unique_cards(const Deck& deck){
    // This deck will contain only the unique cards in `deck`
    Deck unique_cards;
    for (int i = 0; i < count_cards(deck); i++){
        // If the card deck[i] is NOT in the unique_cards deck
        if (!(deck[i] <= unique_cards)){
            // Add the card deck[i] to the unique_cards deck
            unique_cards = unique_cards+deck[i];
        }
    }
    return count_cards(unique_cards);
}

// Cuts `deck` by moving the top half of the cards
// to the bottom of the deck
void cut_deck(Deck& deck){
    // This deck will contain the cards at the top half of `deck`
    static Deck upper_half_deck;
    // The number of cards that make up half the deck
    int upper_half_size = count_cards(deck)/2;
    for (int i =0; i < upper_half_size; i++){
        // Add the card deck[i] to the top of `upper_half_deck`
        upper_half_deck = upper_half_deck+deck[i];
    }
    // Remove the top `upper_half_size` cards from `deck`
    // (The same cards that we added to `upper_half_deck`)
    deck = deck - upper_half_size;
    // Add the cards in `upper_half_deck` to the bottom of `deck`
    deck+=upper_half_deck;
}

int main(){
    cout << "SU Trading Card Game\n";
    string deck_1_file, deck_2_file;

    cout << "Please enter name of the first deck's file: ";
    cin >> deck_1_file;
    ifstream fin1(deck_1_file);
    while (fin1.fail()){
        cout << "File does not exist\n";
        cout << "Please enter name of the first deck's file: ";
        cin >> deck_1_file;
        fin1.open(deck_1_file);
    }

    cout << "Please enter name of the second deck's file: ";
    cin >> deck_2_file;
    ifstream fin2(deck_2_file);
    while (fin2.fail()){
        cout << "File does not exist\n";
        cout << "Please enter name of the first deck's file: ";
        cin >> deck_2_file;
        fin2.open(deck_2_file);
    }

    Deck deck1 = read_deck(fin1);
    Deck deck2 = read_deck(fin2);

    Deck winners_deck;

    cout << "First deck:\n";
    cout << deck1 << endl;;

    cout << "Second deck:\n";
    cout << deck2 << endl;;

    if (deck1 == deck2){
        cout << "Deck 1 and Deck 2 have the same total energy!\n" << endl;
    } else if (deck1 < deck2){
        cout << "Deck 1 has less total energy than Deck 2!\n" << endl;
    } else {
        cout << "Deck 1 has more total energy than Deck 2!\n" << endl;
    }

    cout << "Deck 1 has a total of " << count_cards(deck1) << " cards and " << count_unique_cards(deck1) << " of them are unique.\n";
    cout << "Deck 2 has a total of " << count_cards(deck2) << " cards and " << count_unique_cards(deck2) << " of them are unique.\n";
    cout << endl;
    
    cout << "Cutting deck 1... \n";
    cut_deck(deck1);
    cout << "Deck 1 after cutting:\n";
    cout << deck1 << endl;

    cout << "Cutting deck 2... \n";
    cut_deck(deck2);
    cout << "Deck 2 after cutting:\n";
    cout << deck2 << endl;

    winners_deck = play_game(deck1, deck2);

    cout << endl;

    cout << "The winning deck:\n";
    cout << winners_deck;
    

    return 0;
}
