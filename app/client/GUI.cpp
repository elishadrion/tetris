
#include "GUI.hpp"

/**
 * Constructeur
 */
GUI::GUI() {
    WizardLogger::info("Activation du mode GUI");
}

/**
 * Destructeur
 */
GUI::~GUI() {
    // TO DO
}

void GUI::displayFatalError(std::string error) {}
void GUI::displayLoginPrompt() {
    loginPanel = new LoginPanelGUI();
    loginPanel->show();
}
void GUI::displayLoginResult(std::string message) {
    loginPanel->printLoginResult(message);
    WizardLogger::info("Appel du login result");
}
void GUI::valideLogin() {
    loginPanel->close();
    this->displayMainWindow();
}
void GUI::displayMainWindow() {
    WizardLogger::info("Appel du displayMainWindow");
}
void GUI::displayFriendsWindow() {}
void GUI::displayCollectionWindow() {}
void GUI::displayDeckWindow() {} //TODO get ID ?
void GUI::displayWait() {}
void GUI::displayGame() {}
void GUI::displayClassement() {}
void GUI::focusTchat() {}
void GUI::displayPopup(std::string message) {}
