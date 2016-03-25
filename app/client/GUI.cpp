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


///////////// Game //////////////

void GUI::askDeck() {
    WizardLogger::info("Début du game et choix du deck");
    menuPanel->callInitGame();
}


void GUI::changeTurn(int nbrTurn, bool isTurn) {
    WizardLogger::info("Change turn");
    gamePanel->callChangeTurn(nbrTurn, isTurn);
}

void GUI::drawCard(Card* card) {
    gamePanel->callDrawCard(card);
}

void GUI::adverseDrawCard() {
    gamePanel->callAdvDrawCard();
}

void GUI::placeCard(Card* card) {
    gamePanel->callPlaceCard(card);
}

void GUI::placeAdverseCard(Card * card) {
    gamePanel->callAdvPlaceCard(card);
}

///////////// Tchat /////////////

void GUI::recevTchatMsg(std::string playerFrom, std::string playerTo,
                        std::string msg) {

    WizardLogger::info("Réception du message de " + playerFrom);
    ChatManagerGUI::getInstance()->reqNewMessage(playerFrom, playerTo, msg);
}

///////////// Setter ////////////

void GUI::setMainMenu(MenuPanelGUI* menu) {
    menuPanel = menu;
}


void GUI::setGameMenu(GameGUI* menuGame) {
    gamePanel = menuGame;
}
