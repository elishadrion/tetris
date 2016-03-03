#ifndef CARD_HPP
#define	CARD_HPP

#include <string>

class Card {
    unsigned _id;
    bool _monster;
    std::string _name;
    std::string _description;
    unsigned _energyCost;
    const unsigned _maxHP;
    unsigned _HP;

public:
    explicit Card(unsigned id, bool isMonster, std::string name, std::string description, unsigned energy, unsigned HP) :
        _id(id), _monster(isMonster), _name(name), _description(description), _energyCost(energy),
        _maxHP(HP), _HP(HP) {}
    ~Card() = default;
    
    /* Getter */
    inline unsigned getID() { return _id; }
    inline bool isMonster() { return _monster; }
    inline std::string getName() { return _name; }
    inline std::string getDescription() { return _description; }
    inline unsigned getEnergyCost() { return _energyCost; }
    inline unsigned getMaxHP(){ return _maxHP; }
    inline unsigned getHP(){ return _HP; }
};

#endif	/* CARD_HPP */
