#include "PlayerManager.hpp"
#include "common/Packet.hpp"
#include <typeinfo>

void PlayerManager::loadPlayers() {
    std::ifstream playersFile;
    try {
	playersFile.open(PLAYERS_DB);
    } catch (std::ios_base::failure &fail) {
	WizardLogger::warning("LOADING USERS FAILED");
	return;
    }

    std::string info_str((std::istreambuf_iterator<char>(playersFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json info = nlohmann::json::parse(info_str);

    for (size_t i = 0 ; i < info.size(); ++i) {
	nlohmann::json player_info = info[i];
	_players.push_back(new Player(player_info));
    }
}

std::string PlayerManager::getRanking() {
    std::string ranking;
    std::vector<Player*> sorted_players = std::vector<Player*>(_players);
    std::sort(sorted_players.begin(), sorted_players.end());

    ranking.append("Nom\tVictoires\tDefaites\n");

    for (size_t i = 0; i < sizeof sorted_players; i++)
	ranking << *sorted_players.at(i);

    return ranking;
}


Player* PlayerManager::logIn(std::string username, std::string password, int sockfd) {
    // ce n'est pas mieux de faire un _players.size() plutot qu'un size of ?
    for (size_t i = 0; i < sizeof _players; i++) {
	Player* current = _players.at(i);
	if ((*current).getName() == username &&
	    (*current).getPass() == password) {

	    _connected.push_back(current);
	    current -> updateSockfd(sockfd);
	    return current;
	}
    }
    WizardLogger::warning("NO USER FOUND. LOGIN FAILED");
    return nullptr;
}

Player* PlayerManager::signUp(std::string username, std::string password, int sockfd) {
    nlohmann::json info;
    info["name"] = username;
    info["password"] = password;

    _players.push_back(new Player(info));
    return nullptr;
}
