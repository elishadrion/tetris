#include "WizardDisplay.hpp"

void WizardDisplay::login() {

	bool success = false;
	std::string username;
	std::string password;
    while (!success) {
    	std::cout << "Votre nom d'utilisateur : ";
    	std::getline(std::cin, username);
    	std::cout << "Votre mot de passe : ";
    	std::getline(std::cin, password);

	    pthread_mutex_lock(&packetStackMutex);
	    std::cout<<username<<"|"<<password<<"|"<<std::endl;
	    PacketManager::send_login_request(username.c_str(), password.c_str());
	    
	    pthread_cond_wait(&packetStackCond, &packetStackMutex);
	         
	    if (packetStack.empty()) {
	        WizardLogger::info("Login réussi");
	        success = true;	        

	    } else {
	        
	        packetStack.pop_back();
	    }

	    pthread_mutex_unlock(&packetStackMutex);
	    if (success) {std::cout << "Connecté!" << std::endl;}
	    else{ std::cout << "pas connecté!" << std::endl;}
    }
    	
}



void WizardDisplay::start() {
	login();
	play();
}

void WizardDisplay::play() {
    
	PacketManager::send_play_request();
    //Attend que la room soit complète pour lancer une partie VS
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    WizardLogger::info("On joue!");
    unsigned seed = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    int num = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    game_manager->create_game(num, seed);

}