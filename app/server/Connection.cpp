#include "Connection.hpp"

// Forward declaration. Gateway.
void* handler(void* new_fd);

// get sockaddr, IPv4 or IPv6:
void* Connection::get_in_addr(struct sockaddr *sa) {
    if (sa -> sa_family == AF_INET)
        return &(((struct sockaddr_in*) sa) -> sin_addr);
    return &(((struct sockaddr_in6*) sa) -> sin6_addr);
}


struct addrinfo* Connection::get_machine_info(void) {
    struct addrinfo *all_options;
    struct addrinfo suggestions;
    memset(&suggestions, 0, sizeof(suggestions));
    suggestions.ai_family = AF_UNSPEC;	   // IP agnostic
    suggestions.ai_protocol = IPPROTO_TCP; // TCP protocol
    suggestions.ai_socktype = SOCK_STREAM; // TCP is connection oriented

    int ecode;
    if((ecode = getaddrinfo(NULL, PORT, &suggestions, &all_options)) != 0) {
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

    freeaddrinfo(all_options);     /* No need for this anymore */

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

int Connection::accept_connection(int listening_socket, struct sockaddr_storage * guest) {
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
	FD_SET(new_fd, &master); // adds to master set
	if (new_fd > fdmax) {    // keeps track of the max
	    fdmax = new_fd;
	}

	// network to presentation address
	inet_ntop(guest -> ss_family,
		  get_in_addr(reinterpret_cast<struct sockaddr*>(&guest)),
		  from,
		  INET6_ADDRSTRLEN);
	printf("server - Got connection from: %s\n", from);
    }

    return new_fd;

}

fd_set Connection::master;    // master file descriptor list
fd_set Connection::read_fds;  // temp file descriptor list for select()
int Connection::fdmax;        // maximum file descriptor number



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
        read_fds = master; // copies it
        if (select(fdmax+1, &read_fds, nullptr, nullptr, nullptr) == -1) {
            perror("server - Could not select any socket");
	    exit(EXIT_FAILURE);
        }

        // runs through the existing connections looking for data to read
        for(int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listening_socket) {
                    // handles new connections
		    accept_connection(listening_socket, &guest);
                } else {
		    if (pthread_create(&thread_id, NULL, handler, &i) < 0) {
			perror("server - Could not create thread");
			exit(EXIT_FAILURE);
		    }
                }
            }
	}
    }
}
