#ifndef CollectionPanelCLI_HPP
#define	CollectionPanelCLI_HPP

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "client/PacketManager.hpp"
#include "client/Player.hpp"
#include "client/CacheManager.hpp"
#include "client/Card.hpp"

class CLI;
#include "client/CLI.hpp"

class CLIPanel;
#include "CLIPanel.hpp"

/* define starting line for mainMeny entry */
#define START_LINE 5

class CollectionPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    unsigned currentLine;
public:
    CollectionPanelCLI(CLI*);
    ~CollectionPanelCLI() = default;
    
    void updatePanel();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* CollectionPanelCLI_HPP */
