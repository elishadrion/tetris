#include "Client.hpp"
#include <string>

int main() {
	Client my_client(std::string("127.0.0.1"));
	my_client.start();
	return 0;
}
