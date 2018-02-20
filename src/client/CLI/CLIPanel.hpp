#ifndef CLIPANEL_HPP
#define	CLIPANEL_HPP

#include "../../common/Constants.hpp"

class CLI;
#include "../CLI.hpp"

class CLIPanel {
protected:
    CLI *_cli;
public:
    /* Create or remove interface panel */
    CLIPanel(CLI *cli) : _cli(cli) {}
    virtual ~CLIPanel() = default;
    
    virtual void show() =0;
    virtual void hide() =0;
    virtual void focus() =0;
};

#endif /* CLIPANEL_HPP */
