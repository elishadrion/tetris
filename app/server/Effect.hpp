#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <vector>

class CardMonster;
class PlayerInGame;
class Game;

class Effect { //Abstract class
    static std::vector<Effect*> _listEffect;
    unsigned _id = -1;

public:
    Effect();
    unsigned getId() { return _id; }
    virtual ~Effect(){};

    static void loadAllEffect();
    static Effect* getEffectByID(unsigned);

    virtual void apply(CardMonster*, Game*) = 0;
    virtual void apply(PlayerInGame* player, Game* game) {}; //TO DO (error by default)
    virtual bool isTaunt(){return false;};
    virtual bool canBeApplyOnPlayer(){return false;};
    virtual bool canBeApplyOnCard(){return true;};
};



#endif  /* EFFECT_HPP */
