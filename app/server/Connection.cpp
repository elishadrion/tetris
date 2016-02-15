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

void Connection::mainloop() {
    // setup
    int sockfd = prepare_socket(get_machine_info());
    socklen_t sin_size;
    pthread_t thread_id;
    struct sockaddr_storage guest; // can hold IPv4 or IPv6 addrs.


    std::cout << "Server listening..." << "\n";
    // loop
    while (1) {
	int new_fd;     // where stuff happens
	sin_size = sizeof guest;
	if ((new_fd = accept(sockfd, (struct sockaddr *)&guest, &sin_size)) == -1) {
	    perror("server - Error extracting connection request");
	    exit(EXIT_FAILURE);
	}

	char from[INET6_ADDRSTRLEN];
	// network to presentation address
	inet_ntop(guest.ss_family, Connection::get_in_addr((struct sockaddr*)(&guest)),
		  from, INET6_ADDRSTRLEN);
	printf("server - Got connection from: %s\n", from);

	if (pthread_create(&thread_id, NULL, handler, &new_fd) < 0) {
	    perror("server - Could not create thread");
	    exit(EXIT_FAILURE);
	}
    }
}
