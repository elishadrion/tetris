#include "Client.hpp"
#include <string>

int main(int argc, char* argv[]) {
	Client my_client(std::string("127.0.0.1"));
	my_client.start();
	return 0;
}
