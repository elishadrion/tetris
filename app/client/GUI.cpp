
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

void GUI::displayMainWindow() {
    WizardLogger::warning("Aucune action pour afficher le menu principal");
}

void GUI::displayFriendsWindow() {
    WizardLogger::info("[displayFriendsWindow] Pas encore intégré");
}

void GUI::displayCollectionWindow() {
    WizardLogger::info("[displayCollectionWindow] Pas encore intégré");
}

void GUI::displayDeckWindow() { //TODO get ID ?
    WizardLogger::info("[displayDeckWindow] Pas encore intégré");
}

void GUI::displayWait() {
    WizardLogger::info("[displayWait] Pas encore intégré");
}

void GUI::displayGame() {
    WizardLogger::info("[displayGame] Pas encore intégré");
}

void GUI::displayClassement() {
    WizardLogger::info("[displayClassement] Pas encore intégré");
}

void GUI::focusTchat() {
    WizardLogger::info("[focusTchat] Pas encore intégré");
}

void GUI::displayPopup(std::string message) {
    WizardLogger::info("[displayPopup] Pas encore intégré");
}

void GUI::launchGame(std::string pseudo) {
    WizardLogger::info("Début du game et choix du deck");
    menuPanel->callBeginGame(pseudo);
    // Ask deck
}


void GUI::setMainMenu(MenuPanelGUI* menu) {
    menuPanel = menu;
}
