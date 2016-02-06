/*
 * File:   Login.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 20:01
 */

#ifndef LOGIN_HPP
#define	LOGIN_HPP

#include<string>
#include<vector>

#include "Display.hpp"


/**
 * All functions regarding login
 * I think a class is not necessary but all in one file is not a good idea
 */

class Login : public Display {

    std::vector<std::string> _oldUserName;

public:

    void print() override;


private:
    /**
     * Function when a player will login.  We (crypt the password and) send it on
     * the web server with the username.  Save in the vector the old username
     * (like a cache) so that the next time he could directly chose this username
     *
     * @param username the username
     * @param password the password
     */
    void login(std::string username, std::string password);

    // void disconnect();

    ~Login() = default;
};



#endif	/* LOGIN_HPP */

