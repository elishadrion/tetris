#include <cstdlib>
#include <iostream>

#include "Connection.cpp"

int main(int argc, char** argv) {
    Connection ServerConnection;
    std::cout << "Compiled" << "\n";
    ServerConnection.mainloop();
    return 0;
}
