
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

void GUI::displayFatalError(std::string error) {}

void GUI::displayLoginPrompt() {
    loginPanel = new LoginPanelGUI();
    loginPanel->show();
}

void GUI::displayLoginResult(std::string message) {
    loginPanel->callPrintLoginResult(message);
}

void GUI::valideLogin() {
    loginPanel->callDisplayMainMenu();
}

void GUI::displayMainWindow() {

}

void GUI::displayFriendsWindow() {}
void GUI::displayCollectionWindow() {}
void GUI::displayDeckWindow() {} //TODO get ID ?
void GUI::displayWait() {}
void GUI::displayGame() {}
void GUI::displayClassement() {}
void GUI::focusTchat() {}
void GUI::displayPopup(std::string message) {}
