
#ifndef LOGIN_CPP
#define	LOGIN_CPP


#include "Login.hpp"
#include <iostream>
#include <string>


void Login::login(std::string username, std::string password) {
    // TO DO
}


void Login::print() {

    std::string username;
    std::string pass;


    std::cout << "Username: " << std::endl;
    std::cin >> username;
    std::cout << "Password: " << std::endl;
    std::cin >> pass;


    login(username, pass);
}



#endif /* LOGIN_CPP */
