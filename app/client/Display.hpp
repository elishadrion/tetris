#ifndef DISPLAY_HPP
#define	DISPLAY_HPP

#include <string>

class Display {
public:
    /* Create or remove interface (CLI/GUI) */
    Display() = default;
    virtual ~Display() = default;
    
    /* Must block all display and exit after showing message */
    virtual void displayFatalError(std::string) =0;
    
    /* Only call once, when program begin */
    virtual void displayLoginPrompt() =0;
    
    /* Used to print result of the login process (thread safe) */
    virtual void displayLoginResult(std::string) =0;
    
    /* Validate login process, must call displayMainWindow after */
    virtual void valideLogin() =0;
    
    /* Display the mainWindow
     * Must be safe enought to avoid memory leak or function call hell
     */
    virtual void displayMainWindow() =0;
    
    /* Display friends list */
    virtual void displayFriendsWindow() =0;
    
    /* Display player's collection */
    virtual void displayCollectionWindow() =0;
    
    /* Display player's deck content TODO: get ID ? */
    virtual void displayDeckWindow() =0;
    
    /* Wait for game ready (can cancel ?) */
    virtual void displayWait() =0;
    
    /* Display in-game layout */
    virtual void displayGame() =0;
    
    /* Focus on tchat windows/panel, use it when start a conversation (exemple) */
    virtual void focusTchat() =0;
    
    /* Display popup message */
    virtual void displayPopup(std::string) =0;
};

#endif	/* DISPLAY_HPP */
