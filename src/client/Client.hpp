#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client;

#include <string>

#include "Connection.hpp"
#include "CacheManager.hpp"
#include "Player.hpp"
#include "../common/WizardLogger.hpp"
#include "WizardDisplay.hpp"
#include "GameManager.hpp"

class Client {
	public:
		Client(std::string);
		~Client();
		void start();
		void stop();
};
#endif