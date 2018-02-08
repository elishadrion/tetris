#ifndef CLIENT_HPP
#define CLIENT_HPP

class Client {

    public:
        Client();
        void login();

    private:
    	int sockfd;
	    struct hostent *hostinfo;
	    struct sockaddr_in server_address;
	    pthread_t thread_receive, thread_send;
}

#endif