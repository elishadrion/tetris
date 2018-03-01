#include "WizardDisplay.hpp"

void WizardDisplay::login() {

	bool success = false;
	std::string username;
	std::string password;
    while (!success) {
    	std::cout << "Votre nom d'utilisateur : ";
    	std::getline(std::cin, username);
    	std::cout << "Votre mot de passe : ";
    	std::getline(std::cin, password);

	    pthread_mutex_lock(&packetStackMutex);
	    std::cout<<username<<"|"<<password<<"|"<<std::endl;
	    PacketManager::send_login_request(username.c_str(), password.c_str());
	    
	    pthread_cond_wait(&packetStackCond, &packetStackMutex);
	         
	    if (packetStack.empty()) {
	        WizardLogger::info("Login réussi");
	        success = true;	        

	    } else {
	        
	        packetStack.pop_back();
	    }

	    pthread_mutex_unlock(&packetStackMutex);
	    if (success) {std::cout << "Connecté!" << std::endl;}
	    else{ std::cout << "pas connecté!" << std::endl;}
    }
    	
}



void WizardDisplay::start() {
	login();
	//play();
	menu();
}

void WizardDisplay::play() {
    
	PacketManager::send_play_request();
    //Attend que la room soit complète pour lancer une partie VS
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    WizardLogger::info("On joue!");
    unsigned seed = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    int num = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    game_manager->create_game(num, seed);
    menu();

}

void WizardDisplay::menu() {
	bool is_on_button = true;
 
char *choices[] = { "GAME",
                    "NTM",
                    "PUTE",
                		"EXIT"};
int n_choices = sizeof(choices) / sizeof(char *);

	initscr();
    clear();
    //cbreak(); /* Line buffering disabled. pass on everything */
 
    WINDOW *menu_win;
    menu_win = newwin(24, 80, 0, 0);
    box(menu_win, 0, 0);
    keypad(stdscr, TRUE);
    wrefresh(menu_win);
 
    attron(A_REVERSE);
    mvprintw(23, 0, "Use arrow keys to move, Press enter to select a choice");
    attroff(A_REVERSE);
    refresh();


	int highlight = 1;
    int choice = 0;
    int c;
 
    noecho();
    keypad(menu_win, TRUE);
 
    int x, y, i;   
    x = 2;
    y = 3;
 
    werase(menu_win);
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i){
        if(highlight == i + 1){ /* High light the present choice */
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
    while(1){
        c = wgetch(menu_win);
        switch(c){
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                break;
        }
        int x, y, i;   
    x = 2;
    y = 3;
 
    werase(menu_win);
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i){
        if(highlight == i + 1){ /* High light the present choice */
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
        if (choice == 1){
        	clear();

            play();}
            //return 1;
 
        else if (choice == 2){
        	clear();
        	play();}
            ///register routine
            //return 2;
 
        else if (choice == 3){
        	clear();
        	play();
            break;}
    } 

	// std::cout << "1. Game modes" << std::endl;
	// std::cout << "2. Chat" << std::endl;
	// std::cout << "3. Friends" << std::endl;
	// std::cout << "4. Stats" << std::endl;
	// std::cout << "5. Exit" << std::endl;

	// std::string prout;
	
	// if (ch == 'a') {
	// 	play();
    delwin(menu_win);
	endwin();

	}
