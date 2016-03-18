#ifndef CLIPANEL_HPP
#define	CLIPANEL_HPP

#include "common/Constants.hpp"


class CLIPanel {
public:
    /* Create or remove interface panel */
    CLIPanel() = default;
    virtual ~CLIPanel() = default;
    
    virtual void show() =0;
    virtual void hide() =0;
    virtual void focus() =0;
};

#endif /* CLIPANEL_HPP */
