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

class Deck {
    
    Card _listCard[100];
    std::string name; // name of the deck
    
    
public:
    bool isValide(); // True if there is 100 cards and orther information are true
    void removeCard(int id); // remove a cart or the deck
    void addCard(int id); // add a card in the deck
    
    
    ///// STATIC /////
    std::vector<std::string> getListNameDeck(); // Get the list of the name of deck
    
    
    
};




#endif	/* DECK_HPP */

