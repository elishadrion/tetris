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
	menu();
}

void WizardDisplay::play(int type_game) {
    
	PacketManager::send_play_request(type_game);
    //Attend que la room soit complète pour lancer une partie VS
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    WizardLogger::info("On joue!");
    unsigned seed = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    int num = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    game_manager->start_game(num,type_game, seed);
    menu();

}

void WizardDisplay::menu() {
    bool is_on_button = true;
     
    char *choices[] = { "PLAY GAME",
                    "CHAT",
                    "SETTINGS",
                	"EXIT"
                  };
    int n_choices = sizeof(choices) / sizeof(char *);

	initscr();
    WINDOW *menu_win;
    menu_win = newwin(24, 80, 0, 0);
    noecho();    // On cache les inputs du terminal.
	curs_set(0); // On cac
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
  
    int x, y, i;   
    x = 2;
    y = 3;
     
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
        c = getch();
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
        	wclear(menu_win);
        	clear();
        	wrefresh(menu_win);
        	delwin(menu_win); 
        	endwin();
        	refresh();     	
			choice_game();
            break;}
 
        else if (choice == 2){
        	clear();
            }
            ///register routine
            //return 2;
 
        else if (choice == 3){
        	clear();
        	
            break;}
    } 

	 	
    

	}



void WizardDisplay::choice_game() {
    bool is_on_button = true;
     
    char *choices[] = { "Classic",
                        "Marathon",
                        "Sprint",
                        "VS"
                  };
    int n_choices = sizeof(choices) / sizeof(char *);

    initscr();
    WINDOW *menu_choice_game;
    menu_choice_game = newwin(24, 80, 0, 0);
    noecho();    // On cache les inputs du terminal.
    curs_set(0); // On cac
    box(menu_choice_game, 0, 0);
    keypad(stdscr, TRUE);
    wrefresh(menu_choice_game);
 
    attron(A_REVERSE);
    mvprintw(23, 0, "Use arrow keys to move, Press enter to select a choice");
    attroff(A_REVERSE);
    refresh();


    int highlight = 1;
    int choice = 0;
    int c;
  
    int x, y, i;   
    x = 2;
    y = 3;
     
    box(menu_choice_game, 0, 0);
    for(i = 0; i < n_choices; ++i){
        if(highlight == i + 1){ /* High light the present choice */
            wattron(menu_choice_game, A_REVERSE);
            mvwprintw(menu_choice_game, y, x, "%s", choices[i]);
            wattroff(menu_choice_game, A_REVERSE);
        }
        else
            mvwprintw(menu_choice_game, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_choice_game);
    while(1){
        c = getch();
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
 
   
    box(menu_choice_game, 0, 0);
    for(i = 0; i < n_choices; ++i){
        if(highlight == i + 1){ /* High light the present choice */
            wattron(menu_choice_game, A_REVERSE);
            mvwprintw(menu_choice_game, y, x, "%s", choices[i]);
            wattroff(menu_choice_game, A_REVERSE);
        }
        else
            mvwprintw(menu_choice_game, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_choice_game);
        if (choice == 4){
            wclear(menu_choice_game);
            clear();
            wrefresh(menu_choice_game);
            delwin(menu_choice_game); 
            endwin();
            refresh();  
            play(choice);              
           break;
        }
 
        else if (choice == 2){
            clear();
            play(choice);}
           
 
        else if (choice == 3){
            clear();
            play(choice);
            break;}
    } 

        
    

    }

