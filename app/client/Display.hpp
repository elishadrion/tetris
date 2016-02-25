#ifndef DISPLAY_HPP
#define	DISPLAY_HPP

#include <string>

class Display {
public:
    /* Create or remove interface (CLI/GUI) */
    Display() = default;
    virtual ~Display() = default;
    
    virtual void displayLoginPrompt() =0;
    virtual void displayLoginResult(std::string) =0;
    virtual void valideLogin() =0;
    virtual void displayMainWindow() =0;
};

#endif	/* DISPLAY_HPP */
