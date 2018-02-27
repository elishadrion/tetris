#include "Server.hpp"

void Server::start() {
	WizardLogger::initLogger(true, "WizardLoggerServer");
    WizardLogger::info("Démarrage serveur");
	WizardLogger::info("Ecoute des tentatives de connexions");
    _conn->start();
}

void Server::stop() {
	_conn->stop();
	WizardLogger::info("Arrête du serveur");
}