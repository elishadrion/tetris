#include "GamePanelCLI.hpp"

GamePanelCLI::GamePanelCLI(CLI* cli) : CLIPanel(cli), _ennemyHandSize(0)  {
    /* We create mainWindow where player can select what to do */
    window = newwin(MAIN_HEIGTH, MAIN_WIDTH, 0, 0);
    box(window, 0, 0);

    /* Attach a panel to window */
    panel = new_panel(window);

    /* Update the stacking order */
    update_panels();
    doupdate();
    
    /* Draw trash */
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 2, 2, "#######");
    mvwprintw(window, 3, 2, "#     #");
    mvwprintw(window, 4, 2, "#TRASH#");
    mvwprintw(window, 5, 2, "#     #");
    mvwprintw(window, 6, 2, "#######");
    wattroff(window, COLOR_PAIR(1));
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, MAIN_HEIGTH-6, 2, "#######");
    mvwprintw(window, MAIN_HEIGTH-5, 2, "#     #");
    mvwprintw(window, MAIN_HEIGTH-4, 2, "#TRASH#");
    mvwprintw(window, MAIN_HEIGTH-3, 2, "#     #");
    mvwprintw(window, MAIN_HEIGTH-2, 2, "#######");
    wattroff(window, COLOR_PAIR(2));
    
    /* Draw deck */
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, 2, 10, "#######");
    mvwprintw(window, 3, 10, "#     #");
    mvwprintw(window, 4, 10, "#DECK #");
    mvwprintw(window, 5, 10, "#     #");
    mvwprintw(window, 6, 10, "#######");
    wattroff(window, COLOR_PAIR(1));
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, MAIN_HEIGTH-6, 10, "#######");
    mvwprintw(window, MAIN_HEIGTH-5, 10, "#     #");
    mvwprintw(window, MAIN_HEIGTH-4, 10, "#DECK #");
    mvwprintw(window, MAIN_HEIGTH-3, 10, "#     #");
    mvwprintw(window, MAIN_HEIGTH-2, 10, "#######");
    wattroff(window, COLOR_PAIR(2));
    
    refresh();
}

void GamePanelCLI::update() {
    int col = 2;
    
    /* Draw ennemy hand */
    wattron(window, COLOR_PAIR(3));
    char* nbr = (char*) malloc(sizeof(char)*8);
    snprintf(nbr, 8, "#  %d  #", _ennemyHandSize);
    mvwprintw(window, 2, 18, "#######");
    mvwprintw(window, 3, 18, "#     #");
    mvwprintw(window, 4, 18, nbr);
    mvwprintw(window, 5, 18, "#     #");
    mvwprintw(window, 6, 18, "#######");
    free(nbr);
    wattroff(window, COLOR_PAIR(3));
    
    /* Draw our hand */
    wattron(window, COLOR_PAIR(3));
    //Card** posedCard = GameManager::getInstance()->getPosed();
    for (int i = 0 ; i < 5 ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*9);
        //if (posedCard[i] == 0x0)
            snprintf(ID, 9, "#     # ");
        //else if (posedCard[i]->getID() > 9)
            //snprintf(ID, 9, "#  %d # ", posedCard[i]->getID());
        //else if (posedCard[i]->getID() > 99)
            //snprintf(ID, 9, "# %d # ", posedCard[i]->getID());
        //else
            //snprintf(ID, 9, "#  %d  # ", posedCard[i]->getID());
        
        mvwprintw(window, MAIN_HEIGTH-2, 18+(i*8), "####### ");
        mvwprintw(window, MAIN_HEIGTH-3, 18+(i*8), "#     # ");
        mvwprintw(window, MAIN_HEIGTH-4, 18+(i*8), ID);
        mvwprintw(window, MAIN_HEIGTH-5, 18+(i*8), "#     # ");
        mvwprintw(window, MAIN_HEIGTH-6, 18+(i*8), "####### ");
        
        free(ID);
    }
    wattroff(window, COLOR_PAIR(3));
    
    wrefresh(window);
    
    /* Draw ennemy posed card */
    wattron(window, COLOR_PAIR(1));
    Card** ennemyPosed = GameManager::getInstance()->getAdversePosed();
    for (int i = 0 ; i < MAX_POSED_CARD ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*9);
        if (ennemyPosed[i] == 0x0)
            snprintf(ID, 9, "#     # ", ennemyPosed[i]);
        else if (ennemyPosed[i]->getID() > 9)
            snprintf(ID, 9, "#  %d # ", ennemyPosed[i]->getID());
        else if (ennemyPosed[i]->getID() > 99)
            snprintf(ID, 9, "# %d # ", ennemyPosed[i]->getID());
        else
            snprintf(ID, 9, "#  %d  # ", ennemyPosed[i]->getID());
        
        mvwprintw(window, 7, col+(i*8), "####### ");
        mvwprintw(window, 8, col+(i*8), "#     # ");
        mvwprintw(window, 9, col+(i*8), ID);
        mvwprintw(window, 10, col+(i*8), "#     # ");
        mvwprintw(window, 11, col+(i*8), "####### ");
        
        free(ID);
    }
    wattroff(window, COLOR_PAIR(1));
    
    /* Draw our posed card */
    wattron(window, COLOR_PAIR(2));
    Card** posedCard = GameManager::getInstance()->getPosed();
    for (int i = 0 ; i < MAX_POSED_CARD ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*9);
        if (posedCard[i] == 0x0)
            snprintf(ID, 9, "#     # ");
        else if (posedCard[i]->getID() > 9)
            snprintf(ID, 9, "#  %d # ", posedCard[i]->getID());
        else if (posedCard[i]->getID() > 99)
            snprintf(ID, 9, "# %d # ", posedCard[i]->getID());
        else
            snprintf(ID, 9, "#  %d  # ", posedCard[i]->getID());
        
        mvwprintw(window, MAIN_HEIGTH-11, col+(i*8), "####### ");
        mvwprintw(window, MAIN_HEIGTH-10, col+(i*8), "#     # ");
        mvwprintw(window, MAIN_HEIGTH-9, col+(i*8), ID);
        mvwprintw(window, MAIN_HEIGTH-8, col+(i*8), "#     # ");
        mvwprintw(window, MAIN_HEIGTH-7, col+(i*8), "####### ");
        
        free(ID);
    }
    wattroff(window, COLOR_PAIR(2));
    
    wrefresh(window);
}

void GamePanelCLI::show() {
    show_panel(panel);
    update_panels();
    doupdate();
    
    /* Update display */
    update();
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
