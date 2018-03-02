#include "PlayerManager.hpp"

Game_CLI * display_game;

bool PlayerManager::player_connected(const std::string& usr) {
    for (size_t i = 0; i < g_connected.size(); i++) {
        Player* current = g_connected.at(i);
        
        if (current->get_username() == usr) {
            return true;
        }
    }
    return false;
}

bool PlayerManager::player_existing(const std::string& usr) {
    csv::Parser file = csv::Parser("../../data/database.csv");
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == usr) {
            return true;
        }
    }
    return false;
}

Player* PlayerManager::find_player(char* char_username) {
    std::string str_username = std::string(char_username);
    for (auto it = g_connected.begin(); it != g_connected.end(); it++) {
        if (((*it)->get_username()) == str_username) {
            return *it;
        }
    }
    return nullptr;
}


Player* PlayerManager::login(std::string username, std::string password, int sockfd) {
    WizardLogger::warning("Paquet de login reçu");

    Player* player = nullptr;
    if (!player_connected(username)) {

        csv::Parser file = csv::Parser("../../data/database.csv");
        for (unsigned i = 0; i < file.rowCount(); i++) {
            if (file[i][0] == username && file[i][1] == password) {
                player = new Player(username, sockfd);
                g_connected.push_back(player);
                player->set_sockfd(sockfd);
                break;
            }
        }
    }
    return player;
}

Player* PlayerManager::signup(std::string username, std::string password, int sockfd) {

    Player* player = nullptr;

    if(username.size() > MAX_PSEUDO_SIZE) {
        username = username.substr(0, MAX_PSEUDO_SIZE);
    }

    if (!player_existing(username)) {
        std::ofstream outfile;
        outfile.open("../../data/database.csv", std::ios_base::app);
        outfile << "\n" << username << "," << password << std::endl;
        player = new Player(username, sockfd);
        g_connected.push_back(player);
        player->set_sockfd(sockfd);
    }

    return player;
}


void PlayerManager::logout(Player* player) {
    for (size_t i = 0; i < g_connected.size(); i++) {
        Player* current = g_connected.at(i);

	    if (current == player) {
	        g_connected.erase(g_connected.begin()+i);
	        return;
	    }
    }
}

Room* PlayerManager::create_new_room() {
    Room* new_room = new Room(2);
    g_rooms.push_back(new_room);
    return new_room;
}

void PlayerManager::broadcast_game_ready(Room* room) {
    PacketManager::send_game_waiting(room->get_player(room->get_size()-1));
    for (unsigned i = 0; i < room->get_size(); i++) {
        PacketManager::send_game_ready(room->get_player(i), room->get_seed());
    }

}

void PlayerManager::manage_new_player(Player* player) {
    Room* room = find_available_room();
    if (room == nullptr) room = create_new_room();
    room->add_player(player);

    if(room->is_full()) {
    	broadcast_game_ready(room);
    	start_game(room);
    }
    else PacketManager::send_game_waiting(player);
}

Room* PlayerManager::find_available_room() {
    for (auto it = g_rooms.begin(); it != g_rooms.end(); it++) {
        if (!(*it)->is_full()) {
            return *it;
        }
    }
    return nullptr;
}

void PlayerManager::start_game(Room* room) {
    //gui = new vsGUI();
    room->set_mode(new Vs(room->get_seed()));
    room->get_mode()->init_game(false);
    
    
}