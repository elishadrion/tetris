#ifndef WIZARDDISPLAY_HPP
#define WIZARDDISPLAY_HPP

#include <string>
#include <vector>
#include <pthread.h>



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
    WizardDisplay() = default;
    virtual ~WizardDisplay() = default;

    /* Must block all display and exit after showing message */
    virtual void displayFatalError(std::string) =0;

    /* Only call once, when program begin */
    virtual void displayLoginPrompt() =0;
    
    /* Display error message */
    virtual void diaplayError(std::string) =0;


    /**
     * Call when player win game
     *
     * @param id of win card
     */
    virtual void winGame(int) {}

    /**
     * Call when player loose game
     */
    virtual void looseGame() {}

    /**
     * Call when game is finish (forfait)
     */
    virtual void endGame() {}


    //////////////////////// TCHAT ////////////////////////

    /**
     * Call when player recev message
     * @param playerFrom who send the message
     * @param playerTo who recev the message
     * @param msg the message
     */
    virtual void recevTchatMsg(std::string, std::string, std::string) {} // CLI

};

#endif  /* WIZARDDISPLAY_HPP */