/* 
 * File:   Cards.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 9:01
 */

#ifndef CARD_HPP
#define	CARD_HPP

#include <string>
#include <map>


/**
 * One class per card.  Contain all informations of the card
 */
class Card {
    
    static std::map<int, Card> listCard; // List of card (with id and card)
    
public:
    Card(int id); // Load a card with his id (and stock it in listCard)
    Card(Card card); // copy contructor
    virtual Card copy(); // copy a card
    
    ///// STATIC /////
    static virtual Card getCard(int id); // get a card with his id
    
    
private:
    int _id; // id or the cards
    std::string _name; // name of the cards
    int _energyCost;
    int _heal;
    Effect effect; // His special effect
    
    
    virtual ~Card() = 0; // Abstract class because we cann't instance it
};


Card::~Card() = default;




#endif	/* CARD_HPP */

