#include "WizardDisplay.hpp"

void WizardDisplay::start() {
	bool success = false;
	std::string username;
	std::string password;
	    /* Lock */
    pthread_mutex_lock(&packetStackMutex);
	std::cout << "Entrez votre pseudo : ";
	std::getline(std::cin, username);
	std::cout << "\nEntrez votre mot de passe :";
	std::getline(std::cin, password);
    PacketManager::send_login_request(username.c_str(), password.c_str());
    
    /* Wait for result */
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    
    /* Check result */
    if (packetStack.empty()) {
        WizardLogger::info("Login réussi");
        success = true;
        
        pthread_cond_wait(&packetStackCond, &packetStackMutex);
    } else {
        packetStack.pop_back();
    }
    
    /* Unlock */
    pthread_mutex_unlock(&packetStackMutex);
    
    if (success) std::cout << "Connecté!" << std::endl;
    else std::cout << "pas connecté!" << std::endl;
	
}
