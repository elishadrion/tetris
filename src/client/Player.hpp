#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"

//class CacheManager;
//#include "CacheManager.hpp"


class Player {

    static Player* instance;

    std::string _username;
    unsigned _victories;
    unsigned _defeats;
    //CacheManager *_cm;


public:
    Player(std::string, unsigned, unsigned);
    
    /* Setter */
    inline void increment_victories() { _victories++; }
    inline void increment_defeats() { _defeats++; }
    
    /* Getter */
    inline std::string get_name() const { return _username; }
    inline unsigned get_victories() const { return _victories; }
    inline unsigned get_defeats() const { return _defeats; }

    ~Player() = default;


    static Player* get_player() { return instance; }
};

#endif  /* PLAYER_HPP */
