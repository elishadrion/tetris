#ifndef DECK_HPP
#define	DECK_HPP

#include<string>
#include<vector>

/**
 * A deck is a list of 100 Cards (or less).  Deck only manipulates id (not Cards)
 */
class Deck {

    std::vector<unsigned int>_listCard;
    std::string _name; // name of the deck

private:
    void removeCard(int i); // removes the i-th card from the deck
    void removeIdCard(int id); // removes a card from the deck
    int indexOfCard(int id); // the index of a card
    int getIdOnIndex(int i); // the id of the card at a specific index

public:
    bool isValide(); // True if there is 100 cards and other information are true
    void addCard(int id); // adds a card in the deck
    int pickup();  // Returns a random Card


    ///// STATIC /////
    std::vector<std::string> getListNameDeck(); // Gets the list of the name of the deck



};




#endif	/* DECK_HPP */

