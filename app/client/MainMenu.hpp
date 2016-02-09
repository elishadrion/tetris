/*
 * File:   MainMenu.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 20:09
 */

#ifndef MAINMENU_HPP
#define	MAINMENU_HPP

#include "Display.hpp"


class MainMenu : public Display {

    // STATIC ?
    Display** menu = new Display*[5];


    void choseButton(int number);


public:
    virtual void print() override;
    MainMenu();


};




#endif	/* MAINMENU_HPP */

