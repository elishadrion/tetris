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


void GUI::changeTurn() {
    WizardLogger::info("Change turn");
    gamePanel->callChangeTurn();
}

void GUI::drawCard(Card* card) {
    gamePanel->callDrawCard(card);
}

void GUI::adverseDrawCard() {
    gamePanel->callAdvDrawCard();
}

void GUI::placeAdverseCard(Card * card) {
    gamePanel->callAdvPlaceCard(card);
}

void GUI::placeAdverseSpellCard(Card* card, Card* target) {
    gamePanel->callPlaceAdvSpell(card, target);
}

void GUI::placeAdverseCardAndAttack(Card* card, Card* target) {
    gamePanel->callPlaceAdvCardAttack(card, target);
}

void GUI::placeAdverseSpellPlayer(Card* card) {
    gamePanel->callPlaceAdvSpell(card, nullptr);
}

void GUI::placeAdverseCardAndAttackPlayer(Card* card) {
    gamePanel->callAdvPlaceCard(card);
}

void GUI::adverseAttackCard(Card* card, Card* target) {
    gamePanel->callAdvAttack(card, target);
}

void GUI::adverseAttackPlayer(Card* card) {
    gamePanel->callAdvAttack(card, nullptr);
}


void GUI::cardIsDead(Card* card, bool adv) {
    gamePanel->callDeadCard(card, adv);
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
