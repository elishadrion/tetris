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
	while (1);
}

void Client::receive(int arg) {
	std::cout << "\ndans receive\n";
    int socketfd = (int) arg;
	char server_message[MAXPACKETSIZE];
	while (1) {
		bzero(server_message, MAXPACKETSIZE);
		recv(socketfd, server_message, MAXPACKETSIZE, 0);
		printf("%s", server_message);
	}
}


void Client::send_message(int arg) {
    int socketfd = (int) arg;
    login();
}

void Client::login() {
	std::cout << "\n dans login\n";
    std::string msg = "01:admin:admin:";
    write(sockfd , msg.c_str() , strlen(msg.c_str()));
}
