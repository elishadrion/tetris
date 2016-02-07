#include "Connection.hpp"

struct addrinfo* Connection::get_machine_info(void) const {
    struct addrinfo *machine_info;
    struct addrinfo suggestions;          /* Main data structure */
    memset(&suggestions, 0, sizeof(suggestions));
    suggestions.ai_family = AF_INET6;    /* IPv4 not IPv6 */
    suggestions.ai_protocol = IPPROTO_TCP; /* TCP no raw or UDP */
    suggestions.ai_socktype = SOCK_STREAM; /* TCP connection oriented */

    int ecode;
    if((ecode = getaddrinfo(NULL, PORT, &suggestions, &machine_info)) != 0) {
        printf("server - Failed getting address information: %s\n" , gai_strerror(ecode));
        exit(EXIT_FAILURE);
    }

    return machine_info;
}

int Connection::prepare_socket(struct addrinfo* machine_info) const {
    int sockfd;
    if ((sockfd = socket(machine_info -> ai_family,
             machine_info -> ai_socktype,
             machine_info -> ai_protocol)) == -1) {

        perror("server - Failed creating socket");
        /* and print last error encountered */
        exit(EXIT_FAILURE);
    }

    int reuse_addr_to_true = 1;
    if (setsockopt(sockfd, SOL_SOCKET,
           SO_REUSEADDR, &reuse_addr_to_true, sizeof(int)) == -1) {

        perror("server - Failed setting reuse address option for the socket");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, machine_info -> ai_addr, machine_info -> ai_addrlen) == -1) {
        close(sockfd);
        perror("server - Failed to assign addr to socket file descriptor");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(machine_info);     /* No need for this anymore */

    if (listen(sockfd, BACKLOG)) {
        perror("server - Could not mark the socket referenced by sockfd as passive");
        exit(EXIT_FAILURE);
    }

    return sockfd;

}

// Forward declaration
void* handler(void* new_fd);

void Connection::mainloop() {
    // setup
    int sockfd = prepare_socket(get_machine_info());

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
        inet_ntop(AF_INET6, &(guest.sin6_addr), from, INET6_ADDRSTRLEN);
        printf("server - Got connection from: %s\n", from);

        if (pthread_create(&thread_id, NULL, handler, &new_fd) < 0) {
            perror("server - Could not create thread");
            exit(EXIT_FAILURE);
        }
    }
}