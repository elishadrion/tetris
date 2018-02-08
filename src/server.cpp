#include "server.hpp"
#include "../Group2/src/dependencies/CSVparser/CSVparser.hpp"
#include <fstream>

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

    int socketfd = (int) arg;
    int numbytes;
	char message[MAXPACKETSIZE];
    char code[2];
	string username;

    users[num_users] = new User;
    User user = users[num_users];
    num_users++;

    while (user.is_online()) {
        numbytes = recv(socketfd, message, MAXPACKETSIZE, 0);
        strncpy(code, message, 2);
        switch (code) {

            case '01':
                bool successful_login = login(user, message);
                if (successful_login)
                    send(socketfd, "01:", 4, 0);
                else
                    send(socketfd, "02:", 4, 0);     
                break;

            case '02':
                bool successful_signup = signup(message);
                if (successful_signup)
                    send(socketfd, "01:", 4, 0);
                else
                    send(socketfd, "02:", 4, 0);   
                break;
        }
    }

	close(socketfd);
	pthread_exit(NULL);
     
}

/*
    Connexion de l'utilisateur.
*/
bool login(User& user, char* message) {
    csv::Parser file = csv::Parser("../data/database.csv");
    std::string message;
    message.copy(message, MAXPACKETSIZE, 0);
    std::string username, password;
    extract_credentials(message, username, password);
    //Quitte si l'utilisateur est déjà connecté sur une autre machine
    if (user_already_existing(username)) {
        return false;
    }
    //Vérification que l'utilisateur est bien déjà inscrit
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == username && file[i][1] == password) {
            user.set_username(username);
            return true;
        }
    }
    return false;

}

/*
    Inscription de l'utilisateur.
*/
bool signup(char* message) {
    std::string message;
    message.copy(message, MAXPACKETSIZE, 0);
    std::string username, password;
    extract_credentials(message, username, password);
    if (user_already_existing(username)) {
        return false;
    }
    std::ofstream outfile;
    outfile.open("../data/database.csv", std::ios_base::app);
    outfile << username << "," << password << std::endl; 
    return true;
}

void Server::stop() {
    is_running = false;
    close(server);
    close(client);
}

/*
    Recupère le pseudo ainsi que le mot de passe envoyé par le client.
*/
void extract_credentials(std::string& message, std::string& username, std::string& password) {
    //On commence à 3 car le message est XX:username:password
    //où XX est le code
    std::size_t found1 = message.find(":", 3);
    //cherche la position du dernier :, qui délimite le mdp
    std::size_t found2 = message.find(":", found1+1);
    //on copie dans username, le substring à partir de 3 jusqu'au prochain :
    //donc tout l'username
    if (found1 != std::string::npos)
        username.assign(message, 3, found1-3);
    if (found2 != std::string::npos)
        password.assign(message, found1+1, found2-1-found1);
}

/*
    Renvoie true si un utilisateur avec ce pseudo est déjà connecté.
*/
bool user_already_connected(const std::string& user) {
    for (unsigned i = 0; i < num_users; i++) {
        if (users[i].get_username() == user)
            return true;
    }
    return false;
}

/*
    Renvoie true si un utilisateur avec ce pseudo est déjà inscrit.
*/
bool user_already_existing(const std::string& user) {
    csv::Parser file = csv::Parser("../data/database.csv");
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == username) {
            return true;
        }
    }
    return false;
}