#include "Client.hpp"
#include <string>


int main(int argc, char ** argv) {

	char * address = argv[1];
	if(argc == 1) address = "127.0.0.1";
	Client my_client(address);
    	//Client my_client(std::string("109.129.213.199"));
	my_client.start();
	return 0;
}
