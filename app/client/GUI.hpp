#ifndef GUI_HPP
#define GUI_HPP

#include "Display.hpp"
#include "common/WizardLogger.hpp"
#include "client/GUI/loginPanel.hpp"

class GUI : public Display {
    /* All panel used by the CLI */
    // GUIPanel *_panelList[PANEL_TOTAL_NUMBER];
    /*
    enum panelID {
        LOGIN = 0,
        MAIN = 1,
        TCHAT = 2,
        FRIEND = 3,
        COLL = 4,
        DECK = 5,
        WAIT = 6,
        GAME = 7,
    };*/

public:
    GUI();
    ~GUI();
    void displayFatalError(std::string) override;
    void displayLoginPrompt() override;
    void displayLoginResult(std::string) override;
    void valideLogin() override;
    void displayMainWindow() override;
    void displayFriendsWindow() override;
    void displayCollectionWindow() override;
    void displayDeckWindow() override; //TODO get ID ?
    void displayWait() override;
    void displayGame() override;
    void displayClassement() override;
    void focusTchat() override;
    void displayPopup(std::string) override;
};



#endif // GUI_HPP
