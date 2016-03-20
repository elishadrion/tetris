#ifndef CARD_HPP
#define	CARD_HPP

#include <fstream>
#include <string>
#include <unistd.h>

#include "common/WizardLogger.hpp"

class Card {
    unsigned _id;
    bool _monster;
    std::string _name;
    std::string _description;
    unsigned _energyCost;
    unsigned _attack;
    const unsigned _maxHP;
    unsigned _HP;
    std::string _img;
    bool waitingCache;

    unsigned _position; // Only during the game !

public:
    explicit Card(unsigned id, bool isMonster, std::string name, std::string description, unsigned energy,
                  unsigned HP, unsigned attack) :
        _id(id), _monster(isMonster), _name(name), _description(description), _energyCost(energy),
        _maxHP(HP), _HP(HP), _attack(attack), _img("cache/"+name) {}
    Card(const Card&) = default;
    ~Card() = default;
    
    /* Getter */
    inline unsigned getID() { return _id; }
    inline bool isMonster() { return _monster; }
    inline std::string getName() { return _name; }
    inline std::string getDescription() { return _description; }
    inline unsigned getEnergyCost() { return _energyCost; }
    inline unsigned getMaxHP(){ return _maxHP; }
    inline unsigned getHP(){ return _HP; }
    inline unsigned getAttack() { return _attack; }
    inline void setHP(unsigned heal) { _HP = heal; }
    inline bool isDead() { return _HP <= 0; }
    
    /* Check if img is in cache and ask it if not */
    std::string getImg() {
        /* POSIX access to test if file exist (fatser) */
        if (access(_img.c_str(), F_OK ) == -1) {
            /* If not, we ask server img to write it in cache directory */
            waitingCache = true;
            //TODO PacketManager::askCardImg(_id); [ask to server for img]
            /* Wait for img write to cache */
            while (waitingCache) { usleep(100); }
        }

        return _img;
    }
    
    /* Write img to file in cache */
    void saveImg(const char* data, int size) {
        /* Open the file in binary mode and erase previous file */
        std::ofstream cacheImg(_img, std::ios::out | std::ios::binary);
        
        /* Check if we can access it */
        if (cacheImg.is_open()) {
            /* Write buffer to file */
            cacheImg.write(data, size);
            cacheImg.close();
        } else {
            WizardLogger::error("Impossible d'écrire en cache l'image de la carte"+std::to_string(_id));
            _img = "cache/default";
        }
        
        /* Unblock wainting thread */
        waitingCache = false;
    }

    inline void setPosition(unsigned pos) { _position = pos; }
    inline unsigned getPosition() { return _position; }

};

#endif	/* CARD_HPP */
