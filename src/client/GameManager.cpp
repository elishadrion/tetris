#include "GameManager.hpp"

GameManager* GameManager::_instance;

/**
 * Get the main instance
 *
 * @return the instance of this class
 */
GameManager* GameManager::get_instance() {
    return _instance;
}


/**
 * Constructor
 * @param pseudo of the adverse player
 */
GameManager::GameManager(std::string pseudo): _ennemy(pseudo) {
    _instance = this;
}