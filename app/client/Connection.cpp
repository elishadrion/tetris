#ifndef CONNECTION_CPP
#define	CONNECTION_CPP


#include "Connection.hpp"

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
    suggestions.ai_socktype = SOCK_STREAM; // TCP is connection oriented */

    int ecode;
    if((ecode = getaddrinfo(server, PORT, &suggestions, &all_options)) != 0) {
        printf("client - Failed getting address information: %s\n" , gai_strerror(ecode));
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

	    perror("client - Failed to create socket");
	    continue;
	}

	if (connect(sockfd, helper -> ai_addr,
		    helper -> ai_addrlen) == -1) {
	    close(sockfd);
	    perror("client - Failed to connect using socket");
	    continue;
	}

	break;

    }

    freeaddrinfo(all_options); // all done with this structure

    if (helper == NULL) {
	fprintf(stderr, "client - Failed to connect to any socket on server");
	exit(EXIT_FAILURE);
    }

    // Print network to presentation addr.
    char to[INET6_ADDRSTRLEN];
    inet_ntop(helper -> ai_family, get_in_addr((struct sockaddr*)helper -> ai_addr), to, INET6_ADDRSTRLEN);
    printf("Connecting to %s\n", to);

    return sockfd;

}

void Connection::connect_to_host(char* hostname) {

    int sockfd = prepare_socket(get_server_info(hostname));




    handler(sockfd);
    close(sockfd);
}



#endif	/* CONNECTION_HPP */
