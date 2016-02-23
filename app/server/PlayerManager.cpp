#include "PlayerManager.hpp"
#include "common/Packet.hpp"

void PlayerManager::loadPlayers() {
    std::ifstream playersFile;
    try {
        std::ifstream playersFile(PLAYERS_DB);
    } catch (std::ios_base::failure &fail) {
	WizardLogger::warning("LOADING USERS FAILED");
	return;
    }

    std::string info_str((std::istreambuf_iterator<char>(playersFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json info = nlohmann::json::parse(info_str);


    //Player* signed_in = new Player(info, sockfd);
}

std::string PlayerManager::getRanking() {
    std::string ranking;
    std::vector<Player*> sorted_players = std::vector<Player*>(players);
    std::sort(sorted_players.begin(), sorted_players.end());

    ranking.append("Nom\tVictoires\tDefaites\n");

    for (size_t i = 0; i < sizeof sorted_players; i++)
	ranking << *sorted_players.at(i);

    return ranking;
}


Player* PlayerManager::logIn(Packet::loginRequestPacket req, int sockfd) {
    for (size_t i = 0; i < sizeof players; i++) {
	Player* current = players.at(i);
	if (*current == req) {
	    connected.push_back(current);
	    current -> updateSockfd(sockfd);
	    return current;
	}
    }
    WizardLogger::warning("NO USER FOUND");
    return nullptr;
}

Player PlayerManager::signUp() {

}
