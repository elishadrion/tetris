#include <cstdlib>
#include <iostream>

#include "Connection.hpp"

int main(int argc, char** argv) {
    Connection ServerConnection;
    std::cout << "Compiled" << "\n";
    ServerConnection.mainloop();
    return 0;
}