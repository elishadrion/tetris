#include "Connection.hpp"

Connection::Connection() : ready(false) {
    /* We create informations for use with a socket */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    /* We check/fix size */
    memset(&(server_addr.sin_zero), '\0', 8);


    /* SYS_CALL to create a new socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        WizardLogger::error("Impossible d'avoir un nouveau socket pour le serveur");
        return;
    }

    /* We bind socket with informations */
    if (bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        WizardLogger::error("Impossible d'initialiser le socket du serveur");
        return;
    }

    /* We configure waiting list for the socket */
    if (listen(serverSocket, BACKLOG) == -1) {
        WizardLogger::error("Impossible de mettre en place la file d'attende de connexion");
        return;
    }

    sin_size = sizeof(struct sockaddr_in);
    ready = true;
}

Connection::~Connection() {
    close(serverSocket);
}

bool Connection::isReady() {
    return ready;
}

void Connection::mainLoop() {
    /* We wait for client connection */
    WizardLogger::info("Serveur en attente de connexion client");
    while(1) {
        /* Accept connection and create a new clientSocket */
        int clientSocket = accept(serverSocket, (struct sockaddr *)&client_addr, &sin_size);
        if (clientSocket == -1) {
            WizardLogger::error("Impossible d'accepter la connexion d'un client");
        } else {
            WizardLogger::info("Nouvelle connexion pour le client ");//%s\n", inet_ntoa(client_addr.sin_addr));
            
            //TODO
            int size;
            if (recv(clientSocket, &size, sizeof(int), 0) == 0) {
                WizardLogger::error("Pas de réponse de la part du client");
            }
            WizardLogger::warn("Réception d'un packet de taille : "+std::to_string(size));
            void *packet = malloc(size);
            if (recv(clientSocket, packet, size, 0) == 0) {
                WizardLogger::error("Pas de réponse de la part du client");
            }
            WizardLogger::warn("Tentative d'inderprétation");
            CommService::managePacket(reinterpret_cast<Packet::packet*>(packet));

            /* We create a new Thread for these client and launch it
            if (pthread_create(&thread, NULL, &thread_main, &clientSocket) == -1) {
                perror("Impossible de créer un nouveau thread pour le client");
                close(clientSocket);
            }*/
        }
    }
}

/**
fd_set Connection::master;    // master file descriptor list
fd_set Connection::read_fds;  // temp file descriptor list for select()
int Connection::fdmax;        // maximum file descriptor number

// Forward declaration. Gateway.
void* handler(int &new_fd, int &listening_socket);

int Connection::proper_fd_set(int fd, fd_set* fds, int* fdmax) {
    FD_SET(fd, fds);
    if (fd > *fdmax) {
        *fdmax = fd;
    }
    return 0;
}

int Connection::proper_fd_clr(int fd, fd_set* fds, int* fdmax) {
    FD_CLR(fd, fds);
    if (fd == *fdmax) {
        (*fdmax)--;
    }
    return 0;
}

// get sockaddr, IPv4 or IPv6:
void* Connection::get_in_addr(struct sockaddr_storage * sa) {
    if (sa -> ss_family == AF_INET)
	return &(reinterpret_cast<struct sockaddr_in*>(sa) -> sin_addr);
    return &(reinterpret_cast<struct sockaddr_in6*>(sa) -> sin6_addr);
}


struct addrinfo* Connection::get_machine_info(void) {
    struct addrinfo *all_options;
    struct addrinfo suggestions;
    memset(&suggestions, 0, sizeof(suggestions));
    suggestions.ai_family = AF_UNSPEC;	   // IP agnostic
    suggestions.ai_protocol = IPPROTO_TCP; // TCP protocol
    suggestions.ai_socktype = SOCK_STREAM; // TCP is connection oriented

    int ecode;
    if((ecode = getaddrinfo(nullptr, PORT, &suggestions, &all_options)) != 0) {
	printf("server - Failed getting address information: %s\n" , gai_strerror(ecode));
	exit(EXIT_FAILURE);
    }
    return all_options;
}

int Connection::prepare_socket(struct addrinfo* all_options) {
    int sockfd;
    struct addrinfo *helper;

    int reuse_addr_to_true = 1;

    for (helper = all_options; helper != NULL; helper = helper -> ai_next) {
        if ((sockfd = socket(helper -> ai_family,
			     helper -> ai_socktype,
			     helper -> ai_protocol)) == -1) {
	    perror("server - Failed creating socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET,
		       SO_REUSEADDR, &reuse_addr_to_true,
		       sizeof(int)) == -1) {
	    perror("server - Failed setting reuse address option for the socket");
            exit(EXIT_FAILURE);
        }

        if (bind(sockfd, helper -> ai_addr, helper -> ai_addrlen) == -1) {
            close(sockfd);
	    perror("server - Failed to assign addr to socket file descriptor");
            continue;
        }

        break;
    }
/
    freeaddrinfo(all_options);     // No need for this anymore

    if (helper == NULL)  {
        fprintf(stderr, "server - Could not bind to any address\n");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, BACKLOG)) {
	perror("server - Could not mark the socket referenced by sockfd as passive");
	exit(EXIT_FAILURE);
    }

    return sockfd;
}

int Connection::accept_connection(int listening_socket, struct sockaddr_storage &guest) {
    socklen_t sin_size;
    sin_size = sizeof guest;
    char from[INET6_ADDRSTRLEN];
    int new_fd;

    if ((new_fd = accept(listening_socket,
			 reinterpret_cast<struct sockaddr *>(&guest),
			 &sin_size)) == -1) {
	perror("server - Failed accepting connection request");
	exit(EXIT_FAILURE);
    } else {
	proper_fd_set(new_fd, &master, &fdmax);
	// network to presentation address
	inet_ntop(guest.ss_family,
		  get_in_addr(&guest),
		  from,
		  INET6_ADDRSTRLEN);
	printf("server - Got connection from: %s\n", from);
    }

    return new_fd;

}


void Connection::mainloop() {
    // setup
    int listening_socket = prepare_socket(get_machine_info());
    pthread_t thread_id;
    struct sockaddr_storage guest; // can hold IPv4 or IPv6 addrs.

    FD_ZERO(&master);    // clears the master and temp sets
    FD_ZERO(&read_fds);

    // adds the listener to the master set
    FD_SET(listening_socket, &master);

    // keeps track of the biggest file descriptor
    fdmax = listening_socket; // so far, it's this one

    WizardLogger::info("Server listening...");
    // loop
    while (1) {
        read_fds = master; // copy it
        if (select(fdmax + 1, &read_fds, nullptr, nullptr, nullptr) == -1) {
            perror("server - Could not select any socket");
	    exit(EXIT_FAILURE);
        }

        // runs through the existing connections looking for data to read
        for(int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listening_socket) {
                    // handle new connections
		    accept_connection(listening_socket, guest);
                } else {
		    handler(i, listening_socket);
                }
            }
	}
    }
}
**/
