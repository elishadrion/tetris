#include "Client.hpp"

Client::Client() {
    if ((hostinfo=gethostbyname("127.0.0.1")) == NULL) {
        exit(1);
    }
    
	if ((sockfd=socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		std::cout << "\nImpossible de créer le socket!\n";
		exit(1);
	}
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(5555);
	server_address.sin_addr = *((struct in_addr *)hostinfo->h_addr);
	memset(&(server_address.sin_zero), '\0', 8);
	
	if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        exit(1);
	}
	is_exiting = false;
	std::cout << "\nClient initialisé!\n";
}

void Client::start() {
	std::thread t1(&Client::receive, this);
	std::thread t2(&Client::manage, this);
	t1.detach();
	t2.detach();
	while (!is_exiting);
}

void Client::receive() {
	char server_message[MAXPACKETSIZE];
	std::string message;
	while (1) {
		bzero(server_message, MAXPACKETSIZE);
		recv(sockfd, server_message, MAXPACKETSIZE, 0);
		message = server_message;
		std::cout << message << std::endl;
		if (message == "01:login_green") {
			logged_in = true;
		}
		//std::cout << server_message << std::endl;
	}
}


void Client::manage() {
    while (1) {
    	if (!logged_in)
    		pre_menu();
    	else
    		post_menu();
    		break;
    }
}

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

void Client::post_menu() {
	Game* game = new Game();
	game->start_marathon_game();
	delete game;
}

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
    write(sockfd , msg.c_str() , strlen(msg.c_str()));
}

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
    write(sockfd , msg.c_str() , strlen(msg.c_str()));
}

void Client::exiting() {
	is_exiting = true;
	write(sockfd , "99" , 3);
	
}

std::string Client::get_hash(const std::string& str) {
    std::vector<unsigned char> hash(32);
    picosha2::hash256(str.begin(), str.end(), hash.begin(), hash.end());
    return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
