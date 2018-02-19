#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <vector>
#include <string>

#include "../common/Constants.hpp"
#include "../common/WizardLogger.hpp"
#include "PacketManager.hpp"


class GameManager {

    static GameManager* _instance;

    bool _inGame;
    std::string _ennemy;


public:
    static GameManager* get_instance();

    GameManager(std::string);

    // Getters
    inline bool is_game() const { return _instance != nullptr; }
    inline std::string get_ennemy() const { return _ennemy; }
};




#endif // GAMEMANAGER_HPP
