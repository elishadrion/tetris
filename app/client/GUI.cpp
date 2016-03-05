
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
    //
}

void GUI::displayFatalError(std::string error) {}
void GUI::displayLoginPrompt() {}
void GUI::displayLoginResult(std::string message) {}
void GUI::valideLogin() {}
void GUI::displayMainWindow() {}
void GUI::displayFriendsWindow() {}
void GUI::displayCollectionWindow() {}
void GUI::displayDeckWindow() {} //TODO get ID ?
void GUI::displayWait() {}
void GUI::displayGame() {}
void GUI::displayClassement() {}
void GUI::focusTchat() {}
void GUI::displayPopup(std::string message) {}
