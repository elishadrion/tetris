#include "PlayerManager.hpp"

std::string PlayerManager::getRanking() {
    std::string ranking;
    std::vector<Player*> sorted_players = std::vector<Player*>(players);
    std::sort(sorted_players.begin(), sorted_players.end());

    ranking.append("Nom \t Victoires \t Defaites \n");

    for (size_t i = 0; i < sizeof sorted_players; i++)
	ranking << *sorted_players.at(i);

    return ranking;
}

Player* PlayerManager::signIn(std::string username, std::string pass, int sockfd) {
    std::ifstream playerFile;
    try {
        std::string player_path = PLAYERS_PATH + username + ".json";
        std::ifstream playerFile(player_path);
    } catch (std::ios_base::failure &fail) {
        // No username with that name
        // handle the error
	WizardLogger::warning("LOGIN FAIL");
	return nullptr;
    }

    std::string info_str((std::istreambuf_iterator<char>(playerFile)),
			 std::istreambuf_iterator<char>());
    nlohmann::json info = nlohmann::json::parse(info_str);
    Player* signed_in = new Player(info, sockfd);

    connected.push_back(signed_in);

    return signed_in;

}

Player PlayerManager::signUp() {

}
