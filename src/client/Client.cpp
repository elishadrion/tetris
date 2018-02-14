#include "Client.hpp"

int attente = 0;

Client::Client() {
    if ((_hostinfo=gethostbyname("127.0.0.1")) == NULL) {
        exit(1);
    }
    
	if ((_sockfd=socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		std::cout << "\nImpossible de créer le socket!\n";
		exit(1);
	}
	
	_server_address.sin_family = AF_INET;
	_server_address.sin_port = htons(5555);
	_server_address.sin_addr = *((struct in_addr *)_hostinfo->h_addr);
	memset(&(_server_address.sin_zero), '\0', 8);
	
	if(connect(_sockfd, (struct sockaddr *)&_server_address, sizeof(_server_address)) < 0){
        exit(1);
	}
	_is_exiting = false;
	std::cout << "\nClient initialisé!\n";
}

void Client::start() {
	std::thread t1(&Client::receive, this);
	std::thread t2(&Client::manage, this);
	t1.detach();
	t2.detach();
	while (!_is_exiting);
}

void Client::receive() {
	char server_message[MAXPACKETSIZE];
	std::string message;
	std::queue <std::string>pending_messages;
	while (1) {
		bzero(server_message, MAXPACKETSIZE);
		recv(_sockfd, server_message, MAXPACKETSIZE, 0);
		message = server_message;
		//while (recv(_sockfd, server_message, MAXPACKETSIZE, 0) > 0) {
			//message = server_message;
			//pending_messages.push(message);
		//}
		//message = pending_messages.back();
		//pending_messages.pop();
		if (message == "01:") {
			_logged_in = true;
			attente = 0;
			std::cout << "Vous êtes connectés!\n";
		}
		else if (message == "02:") {
			
			attente = 0;
			_logged_in = false;
			std::cout << "Identifiants invalides!\n";
		}
	}
}


void Client::manage() {
    while (!_is_exiting) {
    	if (attente)
    		;
    		
    	else if (!_logged_in)
    		pre_menu();

    	else
    		post_menu();
    }
}

/*
    Menu affiché tant que l'user n'est pas connecté.
*/
void Client::pre_menu() {
	std::cout << "\n01 pour login, 02 pour signup, 99 pour quitter : ";
	std::string choice;
	std::getline(std::cin, choice);
	if (choice == "01") {
		login();
	}
	else if (choice == "02") {
		signup();
	}
	else if (choice == "99") {
		exiting();
	}
}

/*
    Menu affiché si l'user est connecté.
*/
void Client::post_menu() {
	std::cout << "\n01 pour jouer, 99 pour quitter : ";
	std::string choice;
	std::getline(std::cin, choice);
	if (choice == "01") {
		Game* game = new Game();
		game->start_marathon_game();
		delete game;
	}
	else if (choice == "99") {
		exiting();
	}
}

/*
    Gère la connexion de l'user.
*/
void Client::login() {
	std::string msg = "01:";
	std::string buffer;
	std::cout << "\nEntrez votre pseudo : ";
	std::getline(std::cin, buffer);
	msg.append(buffer);
	msg.append(":");
	std::cout << "\nEntrez votre mot de passe : ";
	std::getline(std::cin, buffer);
	msg.append(get_hash(buffer));
	msg.append(":");
	attente = 1;
    send(_sockfd , msg.c_str() , strlen(msg.c_str()), 0);

}


/*
    Gère l'inscription de l'user.
*/
void Client::signup() {
	std::string msg = "02:";
	std::string buffer;
	std::cout << "\nEntrez votre pseudo : ";
	std::getline(std::cin, buffer);
	msg.append(buffer);
	msg.append(":");
	std::cout << "\nEntrez votre mot de passe : ";
	std::getline(std::cin, buffer);
	msg.append(get_hash(buffer));
	msg.append(":");
    send(_sockfd , msg.c_str() , strlen(msg.c_str()), 0);
}

void Client::exiting() {
	_is_exiting = true;
	send(_sockfd , "99" , 3, 0);
	
}

/*
    Renvoie le hash du mot de passe.
*/
std::string Client::get_hash(const std::string& str) {
    std::vector<unsigned char> hash(32);
    picosha2::hash256(str.begin(), str.end(), hash.begin(), hash.end());
    return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
