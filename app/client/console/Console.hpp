#ifndef CONSOLE_HPP
#define	CONSOLE_HPP

#include <ncurses.h>
#include <cursesp.h>

#define LINES 10
#define COLLONNES 40

class Console {
    NCursesPanel *mainPanel;
    NCursesPanel *loginPanel; //TODO
public:
    Console();
    ~Console();
};

#endif /* CONSOLE_HPP */
