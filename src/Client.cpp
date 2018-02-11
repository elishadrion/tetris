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
	std::cout << "\nClient initialisé!\n";
}

void Client::start() {
	std::thread t1(&Client::receive, this, sockfd);
	std::thread t2(&Client::send_message, this, sockfd);
	t1.detach();
	t2.detach();
	while (1);
}

void Client::receive(int arg) {
    int socketfd = (int) arg;
	char server_message[MAXPACKETSIZE];
	while (1) {
		bzero(server_message, MAXPACKETSIZE);
		recv(socketfd, server_message, MAXPACKETSIZE, 0);
		std::cout << server_message << std::endl;
	}
}


void Client::send_message(int arg) {
    int socketfd = (int) arg;
    char message[MAXPACKETSIZE];
    bzero(message, MAXPACKETSIZE);
    while (1) {
    	std::cout << "\n01 pour login, 02 pour signup : ";
    	std::string choice;
    	std::getline(std::cin, choice);
    	if (choice == "01") {
    		login();
    		Game* game = new Game();
    		game->start_marathon_game();
    		delete game;
    	}
    	else if (choice == "02")
    		signup();
    }
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

std::string Client::get_hash(const std::string& str) {
    std::vector<unsigned char> hash(32);
    picosha2::hash256(str.begin(), str.end(), hash.begin(), hash.end());
    return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
}
