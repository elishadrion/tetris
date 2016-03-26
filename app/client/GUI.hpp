#ifndef GUI_HPP
#define GUI_HPP

#include "WizardDisplay.hpp"
#include "common/WizardLogger.hpp"

#include "client/GUI/LoginPanelGUI.hpp"
#include "client/GUI/MenuPanelGUI.hpp"
#include "client/GUI/GameGUI.hpp"
#include "client/GUI/ChatManagerGUI.hpp"


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

    // Game
    void askDeck() override;
    void changeTurn() override;
    void drawCard(Card*) override;
    void adverseDrawCard() override;
    void placeAdverseCard(Card*) override;
    void placeAdverseSpellCard(Card *, Card *) override;
    void placeAdverseCardAndAttack(Card *, Card *) override;
    void placeAdverseSpellPlayer(Card *) override;
    void placeAdverseCardAndAttackPlayer(Card *) override;
    void cardIsDead(Card*, bool) override;


    // Tchat
    void recevTchatMsg(std::string, std::string, std::string);

    // Setter
    void setMainMenu(MenuPanelGUI*);
    void setGameMenu(GameGUI*);
};



#endif // GUI_HPP
