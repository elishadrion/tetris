#ifndef COLLECTIONPANEL_HPP
#define	COLLECTIONPANEL_HPP

#include <panel.h>
#include <form.h>

#include <string>
#include <vector>

#include "common/WizardLogger.hpp"

#include "client/PacketManager.hpp"

#include "CLIPanel.hpp"

/* define size for panel */
#define COLLECTION_HEIGHT 30
#define COLLECTION_WIDTH 65

/* define starting line for mainMeny entry */
#define START_LINE 5

class CollectionPanel : public CLIPanel {
    WINDOW *window;
    PANEL  *panel;
    
    //TODO use a better item than a vector of int
    std::vector<int> _collection;
public:
    CollectionPanel();
    ~CollectionPanel() = default;
    
    void addCardToCollection(int, int*);
    void updatePanel();
    
    void show() override;
    void hide() override;
    void focus() override;
};

#endif	/* COLLECTIONPANEL_HPP */
