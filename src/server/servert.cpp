#include "Server.hpp"


int main() {
	Server myserver(5555);
	myserver.accept_clients();
	while (1);
	return 0;
}
