#ifndef CARDMONSTER_HPP
#define	CARDMONSTER_HPP

#include "Card.hpp"
#include "Player.hpp"

class CardMonster : virtual public Card {
private:
    std::size_t _life;
    std::size_t _attack;
    std::size_t _maxLife;
    std::size_t _nbrTourPose;

public:
    virtual void dealDamage(CardMonster& otherMonster);
    virtual void dealDamage(Player& player);
    virtual void incrementTour();

    CardMonster(std::size_t id, std::string name, std::size_t energy,
    	Effect effect, bool,std::size_t life, std::size_t attack,
    	std::size_t nbrTour=0);

    CardMonster(CardMonster& otherMonster);

    std::size_t getLife(){return _life;}
    std::size_t getAttack(){return _attack;}
    std::size_t getMaxLife(){return _maxLife;}
    std::size_t getNbrTourPose(){return _tourPose;}

    void setLife(std::size_t newLife){_life = newLife;}
    void setAttack(std::size_t newAttack){_attack = newAttack;}
    void setMaxLife(std::size_t newMax){_maxLife = newMax;}

};




#endif	/* CARDMONSTER_HPP */