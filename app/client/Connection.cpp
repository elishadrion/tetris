#ifndef CONNECTION_CPP
#define	CONNECTION_CPP


#include "Connection.hpp"

void handler(int);

struct addrinfo* Connection::get_server_info(char* server) {
    struct addrinfo *server_info;
    struct addrinfo suggestions;		  /* Main data structure */
    memset(&suggestions, 0, sizeof(suggestions));
    suggestions.ai_family = AF_INET6;	 /* IPv4 not IPv6 */
    suggestions.ai_protocol = IPPROTO_TCP; /* TCP no raw or UDP */
    suggestions.ai_socktype = SOCK_STREAM; /* TCP connection oriented */

    int ecode;
    if((ecode = getaddrinfo(server, PORT, &suggestions, &server_info)) != 0) {
        printf("client - Failed getting address information: %s\n" , gai_strerror(ecode));
        exit(EXIT_FAILURE);
    }

    return server_info;
}

int Connection::prepare_socket(struct addrinfo* server_info) {
    int sockfd;
    if ((sockfd = socket(server_info->ai_family, server_info->ai_socktype,
			 server_info->ai_protocol)) == -1) {

        perror("client: Failed to create socket");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, server_info->ai_addr,
		server_info->ai_addrlen) == -1) {

        close(sockfd);
        perror("client: Failed to connect using socket");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(server_info); // all done with this structure

    return sockfd;
}

void Connection::connect_to_host(char* hostname) {

    char to[INET6_ADDRSTRLEN];
    struct addrinfo* server_info = get_server_info(hostname);
    /* Network to presentation of address, not clean! */
    inet_ntop(AF_INET6, &(((struct sockaddr_in6*)(struct sockaddr *)server_info->ai_addr)->sin6_addr), to, INET6_ADDRSTRLEN);

    int sockfd = prepare_socket(server_info);

    printf("Connecting to %s\n", to);

    handler(sockfd);
    close(sockfd);
}



#endif	/* CONNECTION_HPP */
