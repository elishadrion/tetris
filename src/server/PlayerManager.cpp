#include "PlayerManager.hpp"



bool PlayerManager::player_connected(const std::string& usr) {
    for (size_t i = 0; i < g_connected.size(); i++) {
        Player* current = g_connected.at(i);
        
        if (current->get_username() == usr) {
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
        
        if (db->checkNamePassword(username, password)) {
            player = new Player(username, sockfd);
            g_connected.push_back(player);
            player->set_sockfd(sockfd);

        }
    }
    return player;
}

Player* PlayerManager::signup(std::string username, std::string password, int sockfd) {
	WizardLogger::warning("Paquet d'enregistrement reçu");
    Player* player = nullptr;

    if(username.size() > MAX_PSEUDO_SIZE) {
        username = username.substr(0, MAX_PSEUDO_SIZE);
    }

    if (!db->checkNameExist(username)) {
        db->registerUser(username, password);
        player = new Player(username, sockfd);
        g_connected.push_back(player);
        player->set_sockfd(sockfd);
    }

    return player;
}


void PlayerManager::logout(Player* player) {
    if (player->is_in_chat())
        PacketManager::receive_logout_chat(player); //ENVOI A TOUS LES TCHATCHEUR Qu'il a déco du chat
    for (size_t i = 0; i < g_connected.size(); i++) {
        Player* current = g_connected.at(i);

	    if (current == player) {
	        g_connected.erase(g_connected.begin()+i);
	        return;
	    }
    }
}

Room* PlayerManager::create_new_room(int mode) {
    Room* new_room;
    if(mode ==4){
        new_room = new Room(2);
    }
    else{

        new_room = new Room(1);
    }
    g_rooms.push_back(new_room);
    return new_room;
}

void PlayerManager::broadcast_game_ready(Room* room) {
    PacketManager::send_game_waiting(room->get_player(room->get_size()-1));
    for (unsigned i = 0; i < room->get_size(); i++) {
        PacketManager::send_game_ready(room->get_player(i), room->get_seed());
    }

}

void PlayerManager::manage_new_player(Player* player, int mode) {
    Room* room = find_available_room(mode);
    if (room == nullptr) room = create_new_room(mode);
    room->add_player(player);

    if(room->is_full()) {
    	broadcast_game_ready(room);
    	start_game(room,mode);

    }
    else PacketManager::send_game_waiting(player);
}

Room* PlayerManager::find_available_room(int mode) {
    for (auto it = g_rooms.begin(); it != g_rooms.end(); it++) {
        if (mode == 4 and (*it)->get_max_size() ==2 and !(*it)->is_full()) {
            return *it;
        }
        else if ((*it)->get_max_size() == 1 and !(*it)->is_full()) {
            return *it;
        }
    }
    return nullptr;
}

void PlayerManager::start_game(Room* room, int mode) {
    
    if(mode==1){
        room->set_mode(new Classic(room->get_seed()));        
    }
    else if(mode ==2){
        room->set_mode(new Marathon(room->get_seed()));        
    }
    else if(mode ==3){
        room->set_mode(new Sprint(room->get_seed()));        
    }
    else if(mode ==4){
        room->set_mode(new Vs(room->get_seed()));        
    }

    room->get_mode()->init_game(false);
    std::thread my(&PlayerManager::info_game, room,room->get_mode()->get_stopper());
    my.detach();
    
}





void PlayerManager::info_game(Room * room, Stopper_Thread * stopper){

   unsigned time =0;
   while(!stopper->game_is_finish()){

        sleep(1);
        time+=1;

   }

    std::cout<<room->get_mode()->get_score_player(1)<<std::endl;   
}
