#include "GamePanelCLI.hpp"

GamePanelCLI::GamePanelCLI(CLI* cli) : CLIPanel(cli), ennemyPosedCard({}), posedCard({}), ennemyHandCardNumber({}), handCard({})  {
    /* We create mainWindow where player can select what to do */
    window = newwin(21, 63, 0, 0);
    box(window, 0, 0);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    /* Draw deck */
    attron(COLOR_PAIR(1));
    mvwprintw(window, 2, 2, "#######");
    mvwprintw(window, 3, 2, "#     #");
    mvwprintw(window, 4, 2, "#DECK #");
    mvwprintw(window, 5, 2, "#     #");
    mvwprintw(window, 6, 2, "#######");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvwprintw(window, LINES-6, 2, "#######");
    mvwprintw(window, LINES-5, 2, "#     #");
    mvwprintw(window, LINES-4, 2, "#DECK #");
    mvwprintw(window, LINES-3, 2, "#     #");
    mvwprintw(window, LINES-2, 2, "#######");
    attroff(COLOR_PAIR(2));
    
    /* Draw hand */
    attron(COLOR_PAIR(1));
    mvwprintw(window, 2, 10, "#######");
    mvwprintw(window, 3, 10, "#     #");
    mvwprintw(window, 4, 10, "#HAND #");
    mvwprintw(window, 5, 10, "#     #");
    mvwprintw(window, 6, 10, "#######");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(2));
    mvwprintw(window, LINES-6, 10, "#######");
    mvwprintw(window, LINES-5, 10, "#     #");
    mvwprintw(window, LINES-4, 10, "#HAND #");
    mvwprintw(window, LINES-3, 10, "#     #");
    mvwprintw(window, LINES-2, 10, "#######");
    attroff(COLOR_PAIR(2));
}

void GamePanelCLI::update() {
    int col = 18;
    
    /* Draw ennemy posed card */
    attron(COLOR_PAIR(1));
    for (int i = 0 ; i < ennemyPosedCard.size() ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*7);
        if (ennemyPosedCard[i] > 9)
            snprintf(ID, 7, "#  %d #", ennemyPosedCard[i]);
        else if (ennemyPosedCard[i] > 99)
            snprintf(ID, 7, "# %d #", ennemyPosedCard[i]);
        else
            snprintf(ID, 7, "#  %d  #", ennemyPosedCard[i]);
        
        mvwprintw(window, 2, col+(i*8), "#######");
        mvwprintw(window, 3, col+(i*8), "#     #");
        mvwprintw(window, 4, col+(i*8), ID);
        mvwprintw(window, 5, col+(i*8), "#     #");
        mvwprintw(window, 6, col+(i*8), "#######");
        
        delete ID;
    }
    attroff(COLOR_PAIR(1));
    
    /* Draw our posed card */
    attron(COLOR_PAIR(2));
    for (int i = 0 ; i < posedCard.size() ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*7);
        if (posedCard[i] > 9)
            snprintf(ID, 7, "#  %d #", posedCard[i]);
        else if (posedCard[i] > 99)
            snprintf(ID, 7, "# %d #", posedCard[i]);
        else
            snprintf(ID, 7, "#  %d  #", posedCard[i]);
        
        mvwprintw(window, LINES-5, col+(i*8), "#######");
        mvwprintw(window, LINES-5, col+(i*8), "#     #");
        mvwprintw(window, LINES-4, col+(i*8), ID);
        mvwprintw(window, LINES-3, col+(i*8), "#     #");
        mvwprintw(window, LINES-2, col+(i*8), "#######");
        
        delete ID;
    }
    attroff(COLOR_PAIR(2));
}

void GamePanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
}

void GamePanelCLI::hide() {
    hide_panel(panel);
    update_panels();
    doupdate();
}

void GamePanelCLI::focus() {
    getch();
}
    
void GamePanelCLI::ennemyPoseCard(int cardID) {}
void GamePanelCLI::poseCard(int cardID) {}
void GamePanelCLI::updateEnnemyLife(int amount) {}
void GamePanelCLI::updateLife(int amount) {}
void GamePanelCLI::updateEnergy(int amount) {}
