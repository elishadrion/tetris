#ifndef WIZARDDISPLAY_HPP
#define WIZARDDISPLAY_HPP

#include <string>
#include <vector>


class WizardDisplay {
public:
    /* Create or remove interface (CLI/GUI) */
    WizardDisplay() = default;
    virtual ~WizardDisplay() = default;

    /* Must block all display and exit after showing message */
    virtual void displayFatalError(std::string) =0;

    /* Only call once, when program begin */
    virtual void displayLoginPrompt() =0;

    /* Used to print result of the login process (thread safe) */
    virtual void displayLoginResult(std::string) =0;

    /* Validate login process, must call displayMainWindow after */
    virtual void valideLogin() = 0;

    /* Display the mainWindow
     * Must be safe enought to avoid memory leak or function call hell
     */
    virtual void displayMainWindow() =0;

    /* Display friends list */
    virtual void displayFriendsWindow() =0;

    /* Display player's collection */
    virtual void displayCollectionWindow() =0;

    /* Display player's deck content TODO: get ID ? */
    virtual void displayDeckWindow() =0;

    /* Wait for game ready (can cancel ?) */
    virtual void displayWait() =0;

    /* Display in-game layout */
    virtual void displayGame() =0;

    /* Display classement */
    virtual void displayClassement() =0;

    /* Focus on tchat windows/panel, use it when start a conversation (exemple) */
    virtual void focusTchat() =0;

    /* Display popup message */
    virtual void displayPopup(std::string) =0;

    /* Ask to te play to choose her deck */
    virtual void askDeck() {}

    /* Start game with player in param */
    virtual void launchGame(std::string) {}

    /* Call when a card is placed */
    virtual void placeCard(bool adverse, int cardId) {}

    /* Call when a spell card is placed */
    virtual void placeSpellCard(bool adverse, int cardId) {}

    /* Call when a card is placed and attack other card with spell */
    virtual void placeCardAndSpell(bool adverse, int cardId, int attackCard, unsigned heal) {}

    /* Call when a card attack an other card */
    virtual void attackCard(bool adverse, int cardMakeAttack, int attackCard, unsigned heal) {}

};

#endif  /* WIZARDDISPLAY_HPP */
