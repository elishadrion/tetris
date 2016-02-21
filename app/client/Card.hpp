#ifndef CARD_HPP
#define	CARD_HPP

#include <string>

class Card {
    int _id;
    bool _monster;
    std::string _name;
    std::string _description;
    int _energyCost;
public:
    Card(int id, bool isMonster, std::string name, std::string description, std::size_t energy) :
        _id(id), _monster(isMonster), _name(name), _description(description), _energyCost(energy) {}
    ~Card() = default;
    
    int getId() { return _id; }
    bool isMonster() { return _monster; }
    std::string getName() { return _name; }
    std::string getDescription() { return _description; }
    int getEnergyCost() { return _energyCost; }
};

#endif	/* CARD_HPP */
