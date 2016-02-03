/* 
 * File:   CardCreature.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 9:41
 */

#ifndef CARDCREATURE_HPP
#define	CARDCREATURE_HPP

class CardCreature : public Card {
    
    int _heal;
    int _attack;
    
public:
    virtual void attack();
    
    
    
};




#endif	/* CARDCREATURE_HPP */

