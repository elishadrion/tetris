
#ifndef DECK_HPP
#define	DECK_HPP

#include <string>


class Deck : public Display {
    
    /**
     * Opens the default deck
     */
    void print();
    /**
     * Opens the specific deck
     * 
     * @param name the name of the deck
     */
    void print(std::string name);
    
    
};



#endif	/* DECK_HPP */

