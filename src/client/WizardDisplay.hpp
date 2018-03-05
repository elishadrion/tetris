#ifndef WIZARDDISPLAY_HPP
#define WIZARDDISPLAY_HPP

class WizardDisplay;

#include <string>
#include <iostream>
#include <vector>
#include <pthread.h>


#include "GameManager.hpp"
#include "PacketManager.hpp"
#include "SalonChat.hpp"


extern GameManager* game_manager;
extern SalonChat* salon_chat;

class WizardDisplay {
public:
    #ifndef PACKET_MANAGER_THREAD_SAFE
    #define PACKET_MANAGER_THREAD_SAFE
    pthread_mutex_t packetStackMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t packetStackCond = PTHREAD_COND_INITIALIZER;
    std::vector<void*> packetStack;
    std::vector<int> packetErrorStack;
    #endif
    
    std::string usernameAttribut;
    
    /* Create or remove interface (CLI/GUI) */
    WizardDisplay() = default;
    ~WizardDisplay() = default;

    void start();
	void main_menu();
    void login();
	void register_user();
    void play(int);
    void menu();
    void choice_game();
    
    /* Methode pour le chat */
    void chat();
    void addMsgInChat(char*, char*);

};

#endif  /* WIZARDDISPLAY_HPP */
