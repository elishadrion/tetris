#include "GUI.hpp"


/**
 * Constructeur
 */
GUI::GUI() {
    WizardLogger::info("Activation du mode GUI");

    menuPanel = nullptr;
}

/**
 * Destructeur
 */
GUI::~GUI() {
    // TO DO
    if(loginPanel == nullptr) {
        delete loginPanel;
    }

    if(menuPanel == nullptr) {
        delete menuPanel;
    }
}



///////////// Error /////////////

void GUI::displayFatalError(std::string error) {
    WizardLogger::info("[displayFatalError] Pas encore intégré");
}


void GUI::diaplayError(std::string message) {
    WizardLogger::info("[diaplayError] Pas encore intégré");
}



///////////// Login /////////////

void GUI::displayLoginPrompt() {
    loginPanel = new LoginPanelGUI(this);
    loginPanel->show();
}


void GUI::displayLoginResult(std::string message) {
    loginPanel->callPrintLoginResult(message);
}


void GUI::valideLogin() {
    loginPanel->callDisplayMainMenu();
}



///////////// Game //////////////

void GUI::askDeck() {
    WizardLogger::info("Début du game et choix du deck");
    menuPanel->callInitGame();
}


void GUI::changeTurn(int nbrTurn, bool isTurn) {
    gamePanel->callChangeTurn(nbrTurn, isTurn);
}


///////////// Setter ////////////

void GUI::setMainMenu(MenuPanelGUI* menu) {
    menuPanel = menu;
}


void GUI::setGameMenu(GameGUI* menuGame) {
    gamePanel = menuGame;
}
