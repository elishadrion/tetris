#ifndef SERVER_HPP
#define SERVER_HPP

#include "Connection.hpp"
#include "../common/WizardLogger.hpp"

class Server {
	private:
		Connection* _conn;
	public:
		//CONSTRUCTEUR ET DESTRUCTEUR PAR DEFAUT
		Server(): _conn(new Connection()) {}
		~Server() {delete _conn;}
		//INTERACTIONS
		void start();
		void stop();
};

#endif