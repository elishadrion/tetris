#ifndef CARDMONSTER_HPP
#define	CARDMONSTER_HPP

#include "Card.hpp"
#include "Player.hpp" //TODO tmp patch
#include "PlayerInGame.hpp"


class CardMonster : public Card {
private:
    unsigned int _life;
    unsigned int _attack;
    unsigned int _maxLife;
    unsigned int _nbrTourPose;
    bool _taunt;

public:
    virtual void dealDamage(CardMonster* otherMonster);
    virtual void dealDamage(PlayerInGame& player);
    virtual void incrementTour();

    CardMonster(unsigned int id, std::string name, unsigned int energy,
    	int effect, bool,unsigned int life, unsigned int attack,
    	unsigned int nbrTour=0);

    CardMonster(CardMonster& otherMonster);
    
    virtual ~CardMonster();

    unsigned int getLife(){return _life;}
    unsigned int getAttack(){return _attack;}
    unsigned int getMaxLife(){return _maxLife;}
    unsigned int getNbrTourPose(){return _nbrTourPose;}

    virtual bool isMonster() override { return true; }

    bool isTaunt() { return _taunt; }
    void setTaunt(bool value){_taunt = value;}
    void setLife(unsigned int newLife){_life = newLife;}
    void setAttack(unsigned int newAttack){_attack = newAttack;}
    void setMaxLife(unsigned int newMax){_maxLife = newMax;}
    bool isDead();

    virtual Card* clone();

};




#endif	/* CARDMONSTER_HPP */
