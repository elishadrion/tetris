#ifndef WIZARDDISPLAY_HPP
#define WIZARDDISPLAY_HPP

#include <string>
#include <vector>
#include <pthread.h>

#include "Card.hpp"


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

    /* Ask to te play to choose her deck */
    virtual void askDeck() {} // CLI

    /**
     * Call when the player recieve one new card
     *
     * @param card wich is draw
     */
    virtual void drawCard(Card*) {} // CLI

    /**
     * Call when adverse player draw a card
     */
    virtual void adverseDrawCard() {} // CLI

    /**
     * The turn change
     */
    virtual void changeTurn() {} // CLI

    /**
     * Call when adverse player place card
     *
     * @param card which is place
     */
    virtual void placeAdverseCard(Card*) {} // CLI

    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeAdverseSpellCard(Card*, Card*) {} // CLI

    /**
     * Call when a adverse spell card is placed (and attack adverse player)
     *
     * @param the new card
     */
    virtual void placeAdverseSpellPlayer(Card*) {} // CLI

    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeAdverseCardAndAttack(Card*, Card*) {} // CLI

    /**
     * Call when a adverse spell card is placed (and attack other player)
     *
     * @param the new card
     */
    virtual void placeAdverseCardAndAttackPlayer(Card*) {} // CLI

    /**
     * Call when an adverse card attack an other card
     *
     * @param the card wich attack
     * @param the card wich IS attack
     */
    virtual void adverseAttackCard(Card*, Card*) {} // CLI

    /**
     * Call when an adverse card attack current player
     *
     * @param the card wich attack
     */
    virtual void adverseAttackPlayer(Card*) {} // CLI

    /**
     * Call when a card is dead
     * @param card which is dead
     * @param adverse card or not
     */
    virtual void cardIsDead(Card*, bool) {} // CLI

    /**
     * Call when player have a damage and loose heal
     */
    virtual void playerDamage() {}

    /**
     * Call when adverse player have a damange and loose heal
     */
    virtual void advPlayerDamage() {}

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
