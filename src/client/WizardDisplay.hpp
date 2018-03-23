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
#include "SettingsMenu.hpp"
#include "Player.hpp"

extern GameManager* game_manager;
extern SalonChat* salon_chat;
extern Player* player;

class WizardDisplay {

public:

    #ifndef PACKET_MANAGER_THREAD_SAFE
    #define PACKET_MANAGER_THREAD_SAFE
    pthread_mutex_t packetStackMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t packetStackCond = PTHREAD_COND_INITIALIZER;
    std::vector<void*> packetStack;
    std::vector<int> packetErrorStack;
    #endif
        
    /* Create or remove interface (CLI/GUI) */
    WizardDisplay(){};    
    virtual ~WizardDisplay(){};
    virtual void login()=0;
    virtual void register_user()=0;
    virtual void menu()=0; 
    virtual void main_menu()=0;	
    virtual void end_game(info_game)=0;
    virtual void play(int)=0;
    virtual void choice_game()=0;
    virtual void chat()=0;
    virtual void wait_player()=0;
    

};

#endif  /* WIZARDDISPLAY_HPP */
