#include "Server.hpp"
#include "dependencies/CSVparser/CSVparser.hpp"
#include <fstream>

Server::Server(int port) {

    //Connexion socket
    if ((_server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "\nErreur lors de la création du socket serveur\n";
        exit(1);
    }
    std::cout << "\nSocket serveur créé!\n";

 	memset(&_server_address, 0, sizeof(_server_address));
	_server_address.sin_family=AF_INET;
	_server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	_server_address.sin_port=htons(port);

	//bind permet d'associer un socket à un numéro de port sur la machine locale.
	//Le numérod de port est utilisé pour associer les paquets entrants dans la machine vers un
	//socket descriptor particulier
	if ((bind(_server, (struct sockaddr *)&_server_address, sizeof(_server_address)) <0)) {
        std::cout << "\nErreur lors de la liaison du socket au port\n";
        exit(1);
    }
    _users = new LinkedList();
    _is_running = true;
    listen(_server, 100);
}

Server::~Server() {
	delete _users;
}

/*
    Ecoute s'il y a une connexion d'un client, et si elle est acceptée, un thread est lancé.
*/
void Server::accept_clients() {
	std::cout << "\nOn attend de nouveaux clients!\n";
    _sin_size = sizeof(_client_address);
	while (_is_running) {
		if ((_client = accept(_server, (struct sockaddr*)&_client_address, &_sin_size)) == -1){
			std::cout << "\nClient " << inet_ntoa(_client_address.sin_addr) << " n'a pas pu se connecté\n";
		}
        else {
        	std::cout << "\nClient " << inet_ntoa(_client_address.sin_addr) << " s'est connecté!\n";
		    std::thread t(&Server::receive, this, _client);
		    t.detach();
        }
		
	}
    stop();
}

/*
    Fonction appelée par le thread. Gère les messages venant du client et en renvoient, si nécessaire.
*/
void Server::receive(int arg) {
    int socketfd = arg;
    int numbytes;
    bool done = false;
	char message[MAXPACKETSIZE];
    std::string code;
	std::string username;
    std::string answer;
	
	User* user = new User();
    
    while (!done) {
        numbytes = recv(socketfd, message, MAXPACKETSIZE, 0);
        std::cout << "message reçu : " << message << std::endl;
        code.assign(message, 2);

        if (code == "01")
        	answer = login(user, message);

        else if (code == "02")
            answer = signup(message);
        
        else if (code == "99")
        	done = true;
        	
        send(socketfd, answer.c_str(), strlen(answer.c_str()), 0);
    }
    
	close(socketfd);
     
}

/*
    Connexion de l'utilisateur.
*/
std::string Server::login(User* user, char* arg) {
    csv::Parser file = csv::Parser("../data/database.csv");
    bool successful_login = true;
    std::string message = arg;
    std::string username, password;
    extract_credentials(message, username, password);
    //Quitte si l'utilisateur est déjà connecté sur une autre machine
    if (user_already_connected(username)) {
        successful_login = false;
    }
    //Vérification que l'utilisateur est bien déjà inscrit
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == username && file[i][1] == password) {
            user->set_username(username);
        }
    }
    
    if (successful_login) {
    	std::cout << "login successful!\n";
        _users->prepend(user);
        return std::string("01:login_green");
    }
    else {
    	std::cout << "login unsuccessful!\n";
        return std::string("01:login_red");
    } 

}

/*
    Inscription de l'utilisateur.
*/
std::string Server::signup(char* arg) {
	bool successful_signup = true;
    std::string message = arg;
    std::string username, password;
    extract_credentials(message, username, password);
    if (user_already_existing(username)) {
        successful_signup = false;
    }
    std::ofstream outfile;
    outfile.open("../data/database.csv", std::ios_base::app);
    outfile << "\n" << username << "," << password << std::endl;
    
    if (successful_signup)
    	return std::string("02:register_green");
    else
    	return std::string("02:register_red"); 
}

void Server::stop() {
    _is_running = false;
    close(_server);
    close(_client);
}

/*
    Recupère le pseudo ainsi que le mot de passe envoyé par le client.
*/
void Server::extract_credentials(std::string& message, std::string& username, std::string& password) {
    //On commence à 3 car le message est XX:username:password
    //où XX est le code
    std::size_t found1 = message.find(":", 3);
    //cherche la position du dernier :, qui délimite le mdp
    std::size_t found2 = message.find(":", found1+1);
    //on copie dans username, le substring à partir de 3 jusqu'au prochain :
    //donc tout l'username
    username.assign(message, 3, found1-3);
    password.assign(message, found1+1, found2-1-found1);
}

/*
    Renvoie true si un utilisateur avec ce pseudo est déjà connecté.
*/
bool Server::user_already_connected(const std::string& usr) {
	Node* current = _users->get_head();
	while (current != nullptr){
		if (current->user->get_username() == usr) {
            return true;
        }
        current = current->next;
    }
    return false;
}

/*
    Renvoie true si un utilisateur avec ce pseudo est déjà inscrit.
*/
bool Server::user_already_existing(const std::string& user) {
    csv::Parser file = csv::Parser("../data/database.csv");
    for (unsigned i = 0; i < file.rowCount(); i++) {
        if (file[i][0] == user) {
            return true;
        }
    }
    return false;
}
