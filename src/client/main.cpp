#include "Client.hpp"
#include <string>


int main(int argc, char ** argv) {

	Client my_client(argv[1]);
    	//Client my_client(std::string("109.129.213.199"));
	my_client.start();
	return 0;
}
