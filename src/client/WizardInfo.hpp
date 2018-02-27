#ifndef WIZARDDISPLAY_HPP
#define WIZARDDISPLAY_HPP

class WizardInfo;

#include <string>
#include <iostream>
#include <vector>
#include <pthread.h>

#include "GameManager.hpp"
#include "PacketManager.hpp"
extern GameManager* game_manager;

class WizardInfo {
public:
    #ifndef PACKET_MANAGER_THREAD_SAFE
    #define PACKET_MANAGER_THREAD_SAFE
    pthread_mutex_t packetStackMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t packetStackCond = PTHREAD_COND_INITIALIZER;
    std::vector<void*> packetStack;
    std::vector<int> packetErrorStack;
    #endif
    
    
    /* Create or remove interface (CLI/GUI) */
    WizardInfo() = default;
    ~WizardInfo() = default;



};

#endif  /* WIZARDDISPLAY_HPP */