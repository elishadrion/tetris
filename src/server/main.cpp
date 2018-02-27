#include "Server.hpp"
int main() {
    Server my_serveur;
    my_serveur.start();
    while (1) {}
    my_serveur.stop();
    return 1;
}
