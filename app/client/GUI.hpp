#ifndef GUI_HPP
#define GUI_HPP

#include "WizardDisplay.hpp"
#include "common/WizardLogger.hpp"

#include "client/GUI/LoginPanelGUI.hpp"
#include "client/GUI/MenuPanelGUI.hpp"
#include "client/GUI/GameGUI.hpp"


#include <QObject>


class GUI : public WizardDisplay, public QObject {

    LoginPanelGUI* loginPanel;
    MenuPanelGUI* menuPanel;
    GameGUI* gamePanel;

public:
    GUI();
    virtual ~GUI();
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

    void launchGame(std::string) override;
    void askDeck() override;


    void setMainMenu(MenuPanelGUI*);
    void setGameMenu(GameGUI*);
};



#endif // GUI_HPP
