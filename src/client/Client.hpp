#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client;

#include <string>

#include "Connection.hpp"
#include "Player.hpp"
#include "../common/WizardLogger.hpp"
#include "CLI.hpp"
#include "GameManager.hpp"
#include "SalonChat.hpp"

class Client {
	public:
		Client(std::string);
		~Client();
		void start();
		void stop();
};
#endif
