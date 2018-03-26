#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <algorithm>

#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"



class Player {

    Player* instance;

    std::string _username;
    unsigned _victories;
    unsigned _defeats;
    //CacheManager *_cm;


public:
    Player(std::string username, unsigned victories, unsigned defeats) :
        _username(username), _victories(victories), _defeats(defeats) {}
    Player(): _victories(0), _defeats(0) {}
    ~Player() = default;

    /* Setter */
    inline void increment_victories() { _victories++; }
    inline void increment_defeats() { _defeats++; }
    inline void set_username(std::string username) {_username = username;}

    /* Getter */
    inline std::string get_username() const { return _username; }
    inline unsigned get_victories() const { return _victories; }
    inline unsigned get_defeats() const { return _defeats; }

};

#endif  /* PLAYER_HPP */
