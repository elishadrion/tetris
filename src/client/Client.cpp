#include "Client.hpp"

Connection *conn;
WizardDisplay *display;
Player *player;
GameManager *game_manager;
SalonChat *salon_chat = new SalonChat();
Game_CLI * display_game;


Client::Client(std::string address) {
    game_manager = new GameManager();

    try {
        WizardLogger::initLogger(false, "WizardLogger");
    } catch (std::exception ex) {
        std::cerr << "Impossible d'initialiser le logger : " << ex.what() << std::endl;
    }
    WizardLogger::info("Démarrage du client");

    try {
        conn = new Connection(address);
    } catch (...) {
        std::cerr << "Communication impossible avec le serveur (voir log)" << std::endl;
    }
	
	display = new WizardDisplay();
}

Client::~Client() {
	delete display;
	delete conn;
	delete game_manager;
}

void Client::start() {
	display->start();
}
