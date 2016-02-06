#include <cstdlib>
#include <iostream>

#include "Connection.hpp"

int main(int argc, char** argv) {
    Connection ConnectionService;
    ConnectionService.connect_to_host(argv[1]);

    return 0;
}
