#include "PlayerManager.hpp"

std::vector<Player*> PlayerManager::_players;

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
    nlohmann::json db = nlohmann::json::parse(info_str);

    for (json::iterator i = db.begin(); i != db.end(); ++i) {
        nlohmann::json player_info = i.value();
        _players.push_back(new Player(player_info));
    }

    playersFile.close();
}

/**
 * Send the ranking of the player
 *
 * @param player who must recieve informations
 */
void PlayerManager::sendRanking(Player* player) {
    // Init var
    std::vector<std::string> list_name;
    std::vector<int> list_victories;
    std::vector<int> list_defeats;

    // Sorted player
    std::vector<Player*> sorted_players(_players);

    std::sort(sorted_players.begin(), sorted_players.end());

    for (size_t i = 0; i < sorted_players.size() && i < MAX_PLAYER_CLASSEMENT; ++i) {
        Player* currentPlayer = sorted_players.at(i);
        list_name.push_back(currentPlayer->getName());
        list_victories.push_back(currentPlayer->getVictories());
        list_defeats.push_back(currentPlayer->getDefeats());
    }

    PacketManager::sendClassement(player, list_name, list_victories, list_defeats);
}


Player* PlayerManager::logIn(std::string username, std::string password, int sockfd) {
    for (size_t i = 0; i < _players.size(); i++) {
        Player* current = _players.at(i);

        if ((*current).getName() == username &&
            (*current).getPass() == password) {

            _connected.push_back(current);
            current->updateSockfd(sockfd);
            return current;
        }
    }
    WizardLogger::warning("NO USER FOUND FOR PSEUDO " + username +". LOGIN FAILED");
    return nullptr;
}

Player* PlayerManager::signUp(std::string username, std::string password, int sockfd) {

    if(username.size() > MAX_PSEUDO_SIZE) {
        username = username.substr(0, MAX_PSEUDO_SIZE);
    }

    for (size_t i = 0; i < _players.size(); i++) {
        Player* current = _players.at(i);

        if (*current == username) {
            WizardLogger::warning("CHOSEN USERNAME (" + username + ") ALREADY EXISTS");
            return nullptr;
        }
    }

    nlohmann::json info;
    info["username"] = username;
    info["password"] = password;
    info["victories"] = 0;
    info["defeats"] = 0;
    std::vector<int> collection;
    for (int i = 1; i <= 100; ++i)
	collection.push_back(i);

    info["collection"] = collection;
    nlohmann::json deck;
    deck["deckName"] = "default";
    std::vector<int> random_deck;
    for (int i = 0; i < 20; ++i) {
        random_deck.push_back(rand() % 100 + 1);
    }

    deck["cards"] = random_deck;
    info["decks"].push_back(deck);

    Player* newPlayer = new Player(info, sockfd);
    _players.push_back(newPlayer);
    _connected.push_back(newPlayer);

    return newPlayer;
}

void PlayerManager::savePlayers() const {
    nlohmann::json db = nlohmann::json::array();
    for (size_t i = 0; i < _players.size(); ++i)
	db.push_back((*_players.at(i)).serialise());

    std::ofstream playersFile(PLAYERS_DB);
    playersFile << db.dump(2);
    playersFile.close();
}
