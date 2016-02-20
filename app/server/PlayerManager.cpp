#include "PlayerManager.hpp"

Player* PlayerManager::signIn(std::string username, std::string pass, int sockfd) {
    try {
	std::string player_path = PLAYERS_PATH + username + ".json";
	std::ifstream playerFile(player_path);
    } catch (std::ios_base::failure &fail) {
	// No username with that name
	// handle the error
    }

    nlohmann::json info;

    info["username"] = username;
    // etc etc with pass and sockfd

    Player* signed_in = new Player(info);
    connected.push_back(signed_in);

    return signed_in;

}

Player PlayerManager::signUp() {

}
