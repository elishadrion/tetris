#include "Client.hpp"
#include <string>

int main() {
	//Client my_client(std::string("127.0.0.1"));
    Client my_client(std::string("109.129.213.199"));
	my_client.start();
	return 0;
}
