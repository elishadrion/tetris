/* 
 * File:   CardManager.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 15:00
 */

#ifndef CARDMANAGER_HPP
#define	CARDMANAGER_HPP


/**
 * Load the card and if not exist call the server to get it
 * (Must not be a Class #JavaPower)
 */
class CardManager {
    
    static std::map<int, Card> listCard; // List of card (with id and card)
    
    
public:
    virtual void loadCard(int id);
    
    
    ///// STATIC /////
    static virtual Card getCard(int id); // get a card with his id
    
    
    
};




#endif	/* CARDMANAGER_HPP */

