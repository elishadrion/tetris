
#ifndef PACKAGE_HPP
#define	PACKAGE_HPP

#include<string>

/**
 * Object to send
 * Final information: size|#|channel|#|data
 */
class Package {

    static std::string separation; // string to separate informations

    std::string _channel; // identify the type of informations
    void * _data;




};

std::string Package::separation = "|#|";



#endif	/* PACKAGE_HPP */
