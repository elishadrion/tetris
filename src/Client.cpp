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
}

void Client::login() {
    
}