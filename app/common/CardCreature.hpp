
#ifndef CARDCREATURE_HPP
#define	CARDCREATURE_HPP

class CardCreature : public Card {

    std::size_t _heal;
    std::size_t _attack;

public:
    virtual void attack();



};




#endif	/* CARDCREATURE_HPP */

