#include "User.hpp"

//SETTERS
void User::set_message(std::string str) {
    message.assign(str);
}

void User::set_username(std::string str) {
    username.assign(str);
}


//GETTERS
std::string User::get_message() {
    return message;
}

std::string User::get_username() {
    return username;
}