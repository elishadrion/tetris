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
