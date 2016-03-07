#ifndef CollectionPanelCLI_HPP
#define	CollectionPanelCLI_HPP

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "client/PacketManager.hpp"

#include "CLIPanel.hpp"

/* define starting line for mainMeny entry */
#define START_LINE 5

class CollectionPanelCLI : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    //TODO use a better item than a vector of int
    std::vector<int> _collection;
public:
    CollectionPanelCLI();
    ~CollectionPanelCLI() = default;
    
    void addCardToCollection(int, int*);
    void updatePanel();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* CollectionPanelCLI_HPP */
