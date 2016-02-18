#ifndef CONNECTION_CPP
#define	CONNECTION_CPP


#include "Connection.hpp"
#include "common/WizardLogger.hpp"

/* Initialize connection between client and server
 * @param hostName: hostName where server run
 */
Connection::Connection(char *hostName) : connected(false) {
    if ((host=gethostbyname(hostName)) == NULL) { 
        WizardLogger::error("Impossible de récupérer les infos de connexion au serveur");
        return;
    }

    /* SYS_CALL to create a new socket */
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        WizardLogger::error("Impossible d'avoir un nouveau socket pour le serveur");
        return;
    }
    
    /* We create informations for use with a socket */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *((struct in_addr*)host->h_addr);

    /* We test if struct has good size */
    memset(&(server_addr.sin_zero), '\0', 8);
    
    /* We connect to the server using socket informations */
    WizardLogger::info("Tentative de connexion au serveur");
    if (connect(clientSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        WizardLogger::error("Impossible de se connecter au serveur");
        return;
    }
    
    WizardLogger::info("Connexion réussie");
    connected = true;
}

Connection::~Connection() {
    close(clientSocket);
}

bool Connection::isConnected() {
    return connected;
}

void Connection::sendPacket(Packet *packet, long unsigned int size) {
    WizardLogger::warn("Envoie d'un packet de taille : "+std::to_string(size));
    if (send(clientSocket, &size, sizeof(int), 0) != sizeof(int)) {
        WizardLogger::error("Tout le packet n'a pas été envoyé");
    }
    if (send(clientSocket, packet, size, 0) != size) {
        WizardLogger::error("Tout le packet n'a pas été envoyé");
    }
}

/**
void handler(int);

// get sockaddr, IPv4 or IPv6:
void* Connection::get_in_addr(struct sockaddr *sa) {
    if (sa -> sa_family == AF_INET)
        return &(((struct sockaddr_in*)sa) -> sin_addr);
    return &(((struct sockaddr_in6*)sa) -> sin6_addr);
}

struct addrinfo* Connection::get_server_info(char* server) {
    struct addrinfo *all_options;
    struct addrinfo suggestions;
    memset(&suggestions, 0, sizeof(suggestions));
    suggestions.ai_family = AF_UNSPEC;	   // IPv4 or IPv6
    suggestions.ai_protocol = IPPROTO_TCP; // TCP protocol, not raw or UDP
    suggestions.ai_socktype = SOCK_STREAM; // TCP is connection oriented

    int ecode;
    if((ecode = getaddrinfo(server, PORT, &suggestions, &all_options)) != 0) {
        WizardLogger::error("client - Failed getting address information" , std::system_error(ecode, std::system_category()));
        exit(EXIT_FAILURE);
    }

    return all_options;
}

int Connection::prepare_socket(struct addrinfo* all_options) {
    struct addrinfo* helper;
    int sockfd;
    for (helper = all_options; helper != NULL; helper = helper -> ai_next) {
	if ((sockfd = socket(helper -> ai_family, helper -> ai_socktype,
			     helper -> ai_protocol)) == -1) {

	    WizardLogger::error("client - Failed to create socket");
	    continue;
	}

	if (connect(sockfd, helper -> ai_addr,
		    helper -> ai_addrlen) == -1) {
	    close(sockfd);
	    WizardLogger::error("client - Failed to connect using socket");
	    continue;
	}

	break;

    }

    freeaddrinfo(all_options); // all done with this structure

    if (helper == NULL) {
	    WizardLogger::error("client - Failed to connect to any socket on server");
	    exit(EXIT_FAILURE);
    }

    // Print network to presentation addr.
    char to[INET6_ADDRSTRLEN];
    inet_ntop(helper -> ai_family, get_in_addr((struct sockaddr*)helper -> ai_addr), to, INET6_ADDRSTRLEN);
    WizardLogger::info("Connecting to "); // %s", to);

    return sockfd;

}

void Connection::connect_to_host(char* hostname) {

    Connection::socked = prepare_socket(get_server_info(hostname));




    //handler(sockfd);
    //close(sockfd);
}

void Connection::close_connection() {
    close(Connection::socked);
}

void Connection::sendPacket(Packet *packet, int size) {
    if (send(Connection::socked, packet, size, 0) != size) {
        WizardLogger::error("Tout le packet n'a pas été envoyé");
    }
}
**/


#endif	/* CONNECTION_HPP */
