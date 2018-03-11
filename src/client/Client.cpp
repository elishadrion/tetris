#include "Client.hpp"

Connection *conn;
WizardDisplay *display;
Player *player;
GameManager *game_manager;
SalonChat *salon_chat;
Game_CLI * display_game;
Board* display_game_ui;

Client::Client(std::string address) {
    game_manager = new GameManager(true);
    salon_chat = new SalonChat();
    player = new Player();
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
	
	display = new CLI();
}

Client::~Client() {
	delete display;
	delete conn;
	delete game_manager;
    delete player;
    delete salon_chat;
}

void Client::start() {
	display->main_menu();
}
