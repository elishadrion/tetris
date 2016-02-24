#ifndef DECK_HPP
#define	DECK_HPP

#include<string>
#include<vector>

#include "Collection.hpp"
#include "common/WizardLogger.hpp"
#include "common/Error.hpp"


/**
 * A deck is a list of 20 Cards (or less)
 */
class Deck : Collection {
    std::string _name; // name of the deck

public:
    Deck(std::string name, std::vector<Card*> listCard);
    Deck(std::string name, std::vector<int> listCard);
    Deck(const Deck&); // Copy constructor
    Deck& operator=(const Deck&) = default; // Copy operator

    std::string getName();

    bool isValide(); // True if there is 100 cards and other information are true
    Card* pickup();  // Returns a random Card
    virtual Error addCard(Card* card) override;
    virtual Error addCard(int cardId) override;

    bool deleteDeck(PlayerInGame*);
    Deck* copyDeck();


    static Deck* getDeck(std::string, std::vector<Deck*>);

};




#endif	/* DECK_HPP */

