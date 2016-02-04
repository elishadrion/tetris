/* 
 * File:   Deck.hpp
 * Author: Detobel36
 *
 * Created on 4 février 2016, 9:42
 */

#ifndef DECK_HPP
#define	DECK_HPP

#include <string>


class Deck : public Display {
    
    /**
     * Open the default deck
     */
    void print();
    /**
     * Open the specific deck
     * 
     * @param name the name of the deck
     */
    void print(std::string name);
    
    
};



#endif	/* DECK_HPP */

