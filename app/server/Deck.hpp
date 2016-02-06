/* 
 * File:   Deck.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 9:45
 */

#ifndef DECK_HPP
#define	DECK_HPP

#include<string>
#include<vector>

/**
 * A deck is a list of 100 Cards (or less).  Deck only manipulates id (not Cards)
 */
class Deck {
    
    std::vector<int>_listCard;
    std::string _name; // name of the deck
    
private:
    void removeCard(int i); // remove the i-th cart from the deck
    void removeIdCard(int id); // remove a card from the deck
    int indexOfCard(int id); // the index of a card
    int getIdOnIndex(int i); // the id of the card at a specific index
    
public:
    bool isValide(); // True if there is 100 cards and orther information are true
    void addCard(int id); // add a card in the deck
    int pickup();  // Return a random Card
    
    
    ///// STATIC /////
    std::vector<std::string> getListNameDeck(); // Get the list of the name of deck
    
    
    
};




#endif	/* DECK_HPP */

