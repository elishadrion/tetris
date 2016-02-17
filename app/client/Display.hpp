#ifndef DISPLAY_HPP
#define	DISPLAY_HPP

class Display {
public:
    /* Create or remove interface */
    Display() = default;
    virtual ~Display() = default;
    
    virtual void displayLoginPrompt() =0;
};

#endif	/* DISPLAY_HPP */
