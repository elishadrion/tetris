#include "Client.hpp"

Client::Client() {
    if ((hostinfo=gethostbyname(argv[1])) == NULL) {
        exit();
    }
    
	if ((sockfd=socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		exit();
	}
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr = *((struct in_addr *)hostinfo->h_addr);
	memset(&(server_address.sin_zero), '\0', 8);
	
	if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        exit();
	}
	pthread_create(&thread_receive, NULL, &receive, (void *)sockfd);
	pthread_create(&thread_send, NULL, &send_message, (void *)sockfd);
}

void* Client::receive(void* arg) {
    int socketfd = (int) arg;
	char server_message[MAXPACKETSIZE];
	while (1) {
		bzero(server_message, MAX_SIZE);
		recv(socketfd, server_message, MAX_SIZE, 0);
		printf("%s", server_message);
	}
	pthread_exit(NULL);
}


void* Client::send_message(void* arg) {
    int socketfd = (int) arg;
    login();
}

void Client::login() {
    std::string msg = "01:admin:admin:"
    write(socket , msg , msg.size());
}