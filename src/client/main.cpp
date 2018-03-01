#include "Client.hpp"
#include <string>

int main() {
	Client my_client(std::string("109.134.119.126"));
	my_client.start();
	return 0;
}
