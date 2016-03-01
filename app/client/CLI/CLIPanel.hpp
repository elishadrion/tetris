#ifndef CLIPANEL_HPP
#define	CLIPANEL_HPP

class CLIPanel {
public:
    /* Create or remove interface panel */
    CLIPanel() = default;
    ~CLIPanel() = default;
    
    virtual void show() =0;
    virtual void hide() =0;
    virtual void resize(int, int) =0;
    virtual void focus() =0;
};

#endif /* CLIPANEL_HPP */
