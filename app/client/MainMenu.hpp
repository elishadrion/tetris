/* 
 * File:   MainMenu.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 20:09
 */

#ifndef MAINMENU_HPP
#define	MAINMENU_HPP


class MainMenu : public Display {
    
    static Display menu[5];
    
    MainMenu();
    
    /**
     * function when the player have chose he menu
     * 
     * @param number the button
     */
    void choseButton(int number);
    
    
public:
    virtual void print();
    
    
    
};




#endif	/* MAINMENU_HPP */

