/* 
 * File:   Display.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 20:14
 */

#ifndef DISPLAY_HPP
#define	DISPLAY_HPP


/**
 * Abstract class for the futur display mode. Inherit of this class to display
 * somethink
 */
class Display {
    
    
    virtual void print() = 0; // Console mode
    // virtual void view() = 0;
    
    
    
    virtual ~Display() = 0;
};

Display::~Display() = default;




#endif	/* DISPLAY_HPP */

