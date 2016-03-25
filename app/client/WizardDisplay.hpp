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

    /* Used to print result of the login process (thread safe) */
    virtual void displayLoginResult(std::string) {} // REMOVE

    /* Validate login process, must call displayMainWindow after */
    virtual void valideLogin() {} // REMOVE

    /////////////// MUST BE REMOVE ///////////////////////////////
    virtual void displayMainWindow() {}
    virtual void displayFriendsWindow() {}
    virtual void displayCollectionWindow() {}
    virtual void displayDeckWindow() {}
    virtual void displayWait() {}
    virtual void displayGame() {}
    virtual void displayClassement() {}
    virtual void focusTchat() {}



    /* Display error message */
    virtual void diaplayError(std::string) =0;

    /* Ask to te play to choose her deck */
    virtual void askDeck() {}

    /**
     * Call when the player recieve one new card
     *
     * @param card wich is draw
     */
    virtual void drawCard(Card*) {}

    /**
     * Call when adverse player draw a card
     */
    virtual void adverseDrawCard() {}

    /**
     * The turn change
     *
     * @param nbrTurn since the begin of the game
     * @param isTurn is the player turn of not
     */
    virtual void changeTurn(int, bool) { }


    /**
     * Call when player place card
     *
     * @param card which is place
     */
    virtual void placeCard(Card*) {}

    /**
     * Call when adverse player place card
     *
     * @param card which is place
     */
    virtual void placeAdverseCard(Card*) {}

    /**
     * Call when a spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeSpellCard(Card*, Card*) {}

    /**
     * Call when a spell card is placed (and attack advers player)
     *
     * @param the new card
     */
    virtual void placeSpellPlayer(Card*) {}


    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeAdverseSpellCard(Card*, Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack adverse player)
     *
     * @param the new card
     */
    virtual void placeAdverseSpellPlayer(Card*) {}


    /**
     * Call when card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeCardAndAttack(Card*, Card*) {}

    /**
     * Call when card is placed (and attack adverse player)
     *
     * @param the new card
     */
    virtual void placeCardAndAttackPlayer(Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack an other)
     *
     * @param the new card
     * @param the target card
     */
    virtual void placeAdverseCardAndAttack(Card*, Card*) {}

    /**
     * Call when a adverse spell card is placed (and attack other player)
     *
     * @param the new card
     */
    virtual void placeAdverseCardAndAttackPlayer(Card*) {}

    /**
     * Call when a card attack an other card
     *
     * @param the card wich attack
     * @param the card wich IS attack
     */
    virtual void attackCard(Card*, Card*) {}

    /**
     * Call when an adverse card attack an other card
     *
     * @param the card wich attack
     * @param the card wich IS attack
     */
    virtual void adverseAttackCard(Card*, Card*) {}

    /**
     * Call when a card attack adverse player
     *
     * @param the card wich attack
     */
    virtual void attackPlayer(Card*) {}

    /**
     * Call when an adverse card attack current player
     *
     * @param the card wich attack
     */
    virtual void adverseAttackPlayer(Card*) {}

    //////////////////////// TCHAT ////////////////////////

    /**
     * Call when player recev message
     * @param playerFrom who send the message
     * @param playerTo who recev the message
     * @param msg the message
     */
    virtual void recevTchatMsg(std::string, std::string, std::string) {}

};

#endif  /* WIZARDDISPLAY_HPP */
