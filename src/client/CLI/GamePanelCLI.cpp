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
    
    
    
    wattron(window, COLOR_PAIR(1));
    mvwprintw(window, MAIN_HEIGTH-1, 2, "NE MARCHE PAS !!!");
    wattroff(window, COLOR_PAIR(1));
    
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
    std::vector<Card*> hand = GameManager::getInstance()->getCardInHand();
    for (int i = 0 ; i < 5 ; ++i) {
        char* ID = (char*) malloc(sizeof(char)*9);
        if (hand.size() == 0 || hand[i] == 0x0)
            snprintf(ID, 9, "#     # ");
        else if (hand[i]->getID() > 9)
            snprintf(ID, 9, "#  %d # ", hand[i]->getID());
        else if (hand[i]->getID() > 99)
            snprintf(ID, 9, "# %d # ", hand[i]->getID());
        else
            snprintf(ID, 9, "#  %d  # ", hand[i]->getID());
        
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
    while(true) { getch(); }
}
    
void GamePanelCLI::drawCard(Card* card) {
    _cli->recevTchatMsg(Player::getPlayer()->getName(), "PIOCHE", card->getName());
    update();
}

void GamePanelCLI::adverseDrawCard() {
    _cli->recevTchatMsg(GameManager::getInstance()->getEnnemy(), "PIOCHE", "");
    _ennemyHandSize += 1;
    update();
}

void GamePanelCLI::changeTurn() {
    _cli->recevTchatMsg("GAME", "CHANGEMENT DE TOUR", "");
    update();
}

void GamePanelCLI::placeAdverseCard(Card* card) {
    _cli->recevTchatMsg(GameManager::getInstance()->getEnnemy(), "PLACE", card->getName());
    update();
}

void GamePanelCLI::placeAdverseSpellCard(Card* from, Card* target) {
    _cli->recevTchatMsg(GameManager::getInstance()->getEnnemy(), "SORT", "(see next)");
    if (target != nullptr)
        _cli->recevTchatMsg(from->getName(), target->getName(), "");
    update();
}

void GamePanelCLI::placeAdverseSpellPlayer(Card* card) {
    _cli->recevTchatMsg(GameManager::getInstance()->getEnnemy(), "SORT", card->getName());
    update();
}

void GamePanelCLI::placeCardAndAttack(Card* from, Card* target) {
    _cli->recevTchatMsg(Player::getPlayer()->getName(), "JOUE ET ATTAQUE", "(see next)");
    if (target != nullptr)
        _cli->recevTchatMsg(from->getName(), target->getName(), "");
    update();
}

void GamePanelCLI::placeCardAndAttackPlayer(Card* card) {
    _cli->recevTchatMsg(Player::getPlayer()->getName(), "ATTAQUE JOUEUR", card->getName());
    update();
}

void GamePanelCLI::placeAdverseCardAndAttack(Card* from, Card* target) {
    _cli->recevTchatMsg(Player::getPlayer()->getName(), "JOUE ET ATTAQUE", "(see next)");
    if (target != nullptr)
        _cli->recevTchatMsg(from->getName(), target->getName(), "");
    update();
}

void GamePanelCLI::placeAdverseCardAndAttackPlayer(Card* card) {
    
}

void GamePanelCLI::attackCard(Card* from, Card* target) {
    
}

void GamePanelCLI::adverseAttackCard(Card* from, Card* target) {
    
}

void GamePanelCLI::attackPlayer(Card* card) {
    
}

void GamePanelCLI::adverseAttackPlayer(Card* card) {
    
}

void GamePanelCLI::cardIsDead(Card* card, bool advers) {
    
}

