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

void GUI::displayFatalError(std::string error) {
    WizardLogger::info("[displayFatalError] Pas encore intégré");
}

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


void GUI::diaplayError(std::string message) {
    WizardLogger::info("[displayPopup] Pas encore intégré");
}


void GUI::askDeck() {
    WizardLogger::info("Début du game et choix du deck");
    menuPanel->callInitGame();
}

void GUI::launchGame(std::string pseudo) {
    WizardLogger::info("Début de la partie");
    gamePanel->callStartGame(pseudo);
}


void GUI::setMainMenu(MenuPanelGUI* menu) {
    menuPanel = menu;
}

void GUI::setGameMenu(GameGUI* menuGame) {
    gamePanel = menuGame;
}
