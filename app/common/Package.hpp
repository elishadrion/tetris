/* 
 * File:   Package.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 10:09
 */

#ifndef PACKAGE_HPP
#define	PACKAGE_HPP

#include<string>

/**
 * Object to send
 * Final information: size|#|channel|#|data
 */
class Package {
    
    static std::string _separation = "|#|"; // string to separate informations
    
    std::string _channel; // identify the type of informations
    void * _data;
    
    
    
    
};


#endif	/* PACKAGE_HPP */