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

    // Error
    void displayFatalError(std::string) override;
    void diaplayError(std::string) override;

    // Loggin
    void displayLoginPrompt() override;
    void displayLoginResult(std::string) override;
    void valideLogin() override;

    // Game
    void askDeck() override;
    void changeTurn(int, bool) override;

    // Setter
    void setMainMenu(MenuPanelGUI*);
    void setGameMenu(GameGUI*);
};



#endif // GUI_HPP
