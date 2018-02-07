#include "server.hpp"

Server::Server(int port) {

    //Connexion socket
    if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\nErreur lors de la création du socket serveur\n";
        exit(1);
    }
    std::cout << "\nSocket serveur créé!\n";

 	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(port);

	//bind permet d'associer un socket à un numéro de port sur la machine locale.
	//Le numérod de port est utilisé pour associer les paquets entrants dans la machine vers un
	//socket descriptor particulier
	if ((bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) <0) {
        std::cout << "\nErreur lors de la liaison du socket au port\n";
        exit(1);
    }
    is_running = true;
    listen(sockfd, 100);
}

void Server::accept() {
    sin_size = sizeof(struct sockaddr_in);
	while (is_running) {
		if ((client = accept(server, (struct sockadrr *)&client_address, &sin_size)) == -1){
			std::cout << "\nClient " << inet_ntoa(client_address.sin_addr) << " n'a pas pu se connecté\n";
		}
        else {
		    pthread_create(&thread, NULL, &receive, (void *) client);
        }
		
	}
    stop();
}

void* Server::receive(void* arg) {
    //Quand un thread détaché se termine, ses ressources sont automatiquement
    //retournées au système sans avoir besoin de faire de join
    pthread_detach(pthread_self());
    users[num_users] = new User;
    num_users++;
    if (!signup(users[num_users])) {
        delete users[num_users];
        num_users--;
    }
     
}

bool signup(User * user) {

}

void Server::stop() {
    is_running = false;
    close(server);
    close(client);
}