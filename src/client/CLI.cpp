#include "CLI.hpp"
#include<iostream>

#include "StatisticsManager.hpp"

extern StatisticsManager *statistics_manager;

std::string empty_space_string(const char*str, int len ){

    char c[len+1];
    for(int i=0; i<len;i++){

        c[i] = str[i];

    }
    c[len]='\0';
    std::string v(c);

    return v;
}

CLI::CLI(){

    initscr();
    start_color();
    timeout(-1);
    noecho();    // On cache les inputs du terminal.
    curs_set(0); // On cac
    keypad(stdscr, TRUE);
    

}


void CLI::wait_player(){

    clear();
    mvprintw(LINES /2, COLS/2 -15, "En attente d'un autre joueur ...");
    refresh();

}

CLI::~CLI(){
    endwin();

}

void CLI::login() {

    clear();
  
    curs_set(1);
	bool success = false;
	std::string password;
    while (!success) {

    	FIELD *field[3];
        FORM  *my_form;
        int ch;

        int index_pseudo=0;
        int index_password=0;
        int len_pseudo=0;
        int len_password=0;
        int is_pseudo = 1;

        /* Initialize few color pairs */
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);


        /* Initialize the fields */
        field[0] = new_field(1, 20, 4, 18, 0, 0);
        field[1] = new_field(1, 20, 6, 18, 0, 0);
        field[2] = NULL;

        /* Set field options */
        set_field_fore(field[0], COLOR_PAIR(1));/* Put the field with blue background */
        set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
                            /* are printed in white     */
          /* Don't go to next field when this */
                            /* Field is filled up       */

        set_field_fore(field[1], COLOR_PAIR(1));
        set_field_back(field[1], COLOR_PAIR(2));/* and white foreground (characters */


        /* Create the form and post it */
        my_form = new_form(field);
        post_form(my_form);
        refresh();

        set_current_field(my_form, field[0]); /* Set focus to the colored field */
        
        mvprintw(4, 10, "Pseudo :");
        mvprintw(6, 10, "Code :");
        mvprintw(LINES - 2, 0, "Connectez-vous pour commencer à jouer");
        refresh();

        /* Loop through to get user requests */
        bool flag = false;
        char password_not_hide[20];
        while(not(flag) and (ch = getch()) )
        {   switch(ch)
            {   case KEY_DOWN:
                    /* Go to next field */
                    set_current_field(my_form, field[1]);
                    is_pseudo=0;
                    /* Go to the end of the present buffer */
                    /* Leaves nicely at the last character */

                    break;
                case KEY_UP:
                    /* Go to previous field */

                    set_current_field(my_form, field[0]);
                    is_pseudo =1;
                    break;

                case KEY_BACKSPACE:
                    form_driver(my_form, REQ_LEFT_CHAR);
                    form_driver(my_form, REQ_DEL_CHAR);
                    if(is_pseudo){
                        index_pseudo-=1;
                        len_pseudo-=1;
                    }

                    else{
                        password_not_hide[index_password]=' ';
                        index_password-=1;
                        len_password-=1;
                    }
                    break;
                case 10:

                    if(is_pseudo==1){
                        set_current_field(my_form, field[1]);
                        is_pseudo=0;
                        break;
                    }else{
                        form_driver(my_form, REQ_VALIDATION);
                        flag = true;
                        break;}


                default:
                    /* If this is a normal character, it gets */
                    /* Printed                */

                    if(is_pseudo){

                        form_driver(my_form, ch);
                        index_pseudo+=1;
                        len_pseudo+=1;
                    }

                    else{
                        password_not_hide[index_password] = ch;
                        form_driver(my_form, '*');
                        index_password+=1;
                        len_password+=1;
                    }
                    break;
            }


        }


        std::string pseudo = empty_space_string(field_buffer(field[0], 0), len_pseudo);
        std::string password = empty_space_string(password_not_hide, len_password);

	    pthread_mutex_lock(&packetStackMutex);
        PacketManager::send_login_request(pseudo.c_str(), password.c_str());
	    pthread_cond_wait(&packetStackCond, &packetStackMutex);

	    if (packetStack.empty()) {
	        WizardLogger::info("Login réussi");
	        success = true;
            player->set_username(pseudo);

	    } else {

	        packetStack.pop_back();
	    }

	    pthread_mutex_unlock(&packetStackMutex);

    }

     curs_set(0);

}



void CLI::register_user() {

    clear();

    bool success = false;
    std::string pseudo;
    std::string password;
     curs_set(1);
    while (!success) {

        FIELD *field[3];
        FORM  *my_form;
        int ch;

        int index_pseudo=0;
        int index_password=0;
        int len_pseudo=0;
        int len_password=0;
        int is_pseudo = 1;

        /* Initialize few color pairs */
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_WHITE, COLOR_BLUE);


        /* Initialize the fields */
        field[0] = new_field(1, 20, 4, 18, 0, 0);
        field[1] = new_field(1, 20, 6, 18, 0, 0);
        field[2] = NULL;

        /* Set field options */
        set_field_fore(field[0], COLOR_PAIR(1));/* Put the field with blue background */
        set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
                            /* are printed in white     */
          /* Don't go to next field when this */
                            /* Field is filled up       */

        set_field_fore(field[1], COLOR_PAIR(1));
        set_field_back(field[1], COLOR_PAIR(2));/* and white foreground (characters */


        /* Create the form and post it */
        my_form = new_form(field);
        post_form(my_form);
        refresh();

        set_current_field(my_form, field[0]); /* Set focus to the colored field */
        mvprintw(4, 10, "Pseudo :");
        mvprintw(6, 10, "Code :");
        mvprintw(LINES - 2, 0, "Enrengistrez-vous pour commencer à jouer");
        refresh();

        /* Loop through to get user requests */
        bool flag = false;
        char password_not_hide[20];
        while(not(flag) and (ch = getch()) )
        {   switch(ch)
            {   case KEY_DOWN:
                    /* Go to next field */
                    set_current_field(my_form, field[1]);
                    is_pseudo=0;
                    /* Go to the end of the present buffer */
                    /* Leaves nicely at the last character */

                    break;
                case KEY_UP:
                    /* Go to previous field */

                    set_current_field(my_form, field[0]);
                    is_pseudo =1;
                    break;

                case KEY_BACKSPACE:
                    form_driver(my_form, REQ_LEFT_CHAR);
                    form_driver(my_form, REQ_DEL_CHAR);
                    if(is_pseudo){
                        index_pseudo-=1;
                        len_pseudo-=1;
                    }

                    else{
                        password_not_hide[index_password]=' ';
                        index_password-=1;
                        len_password-=1;
                    }
                    break;
                case 10:

                    if(is_pseudo==1){
                        set_current_field(my_form, field[1]);
                        is_pseudo=0;
                        break;
                    }else{
                        form_driver(my_form, REQ_VALIDATION);
                        flag = true;
                        break;}


                default:
                    /* If this is a normal character, it gets */
                    /* Printed                */

                    if(is_pseudo){

                        form_driver(my_form, ch);
                        index_pseudo+=1;
                        len_pseudo+=1;
                    }

                    else{
                        password_not_hide[index_password] = ch;
                        form_driver(my_form, '*');
                        index_password+=1;
                        len_password+=1;
                    }
                    break;
            }


        }


        pseudo = empty_space_string(field_buffer(field[0], 0), len_pseudo);
        std::string password = empty_space_string(password_not_hide, len_password);


        pthread_mutex_lock(&packetStackMutex);
	    PacketManager::send_signup_request(pseudo.c_str(), password.c_str());
	    pthread_cond_wait(&packetStackCond, &packetStackMutex);

	    if (packetStack.empty()) {
	        WizardLogger::info("Enregistrement réussi");
	        success = true;
	    } else {
	        packetStack.pop_back();
	    }
	    pthread_mutex_unlock(&packetStackMutex);

    }
        player->set_username(pseudo);
        curs_set(0);
}



void CLI::main_menu(){

    clear();
    bool is_on_button = true;
     
    char *choices[] = { "Se connecter",
                        "S'enrengistrer"
                  };
    int n_choices = sizeof(choices) / sizeof(char *);


    WINDOW *menu_win;
    menu_win = newwin(24, 80, 0, 0);

    box(menu_win, 0, 0);


    refresh();
    wrefresh(menu_win);



    int highlight = 1;
    int choice = 0;
    int c;

    int x, y, i;
    x = (COLS / 2) -15 ;
    y =  LINES/2 ;

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

    x = (COLS / 2) -15 ;
    y =  LINES/2 ;


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

            login();
            menu();
            break;}

        else if (choice == 2){

           register_user();
           menu();
           break;

            }

    }
}


void CLI::chat() {
    PacketManager::send_chat_conn(player->get_username().c_str());
    for (int i = 0 ; i < MAX_PSEUDO_SIZE ; ++i) {
        salon_chat->username[i] = player->get_username()[i];
    }
    salon_chat->startChat();
    //APRES AVOIR FINI IL LANCE LE MENU

    menu();
}


void CLI::play(int type_game) {

    PacketManager::send_play_request(type_game);
    //Attend que la room soit complète pour lancer une partie VS

    if(type_game ==4 or type_game == 5){
        pthread_cond_wait(&packetStackCond, &packetStackMutex);
        wait_player();
    }


    pthread_cond_wait(&packetStackCond, &packetStackMutex);
    usleep(10000);

    while(packetStack.size() != 2){};
    WizardLogger::info("On joue!");

    //int x =sizeof(packetStack.back());
    //WizardLogger::info(std::to_string(reinterpret_cast<long>(packetStack.back())));
    long seed = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    long num = reinterpret_cast<long>(packetStack.back());
    packetStack.pop_back();
    WizardLogger::info("seg fault ?");
    timeout(10);
    struct info_game myInfo = game_manager->start_game(num,type_game, seed);
    timeout(-1);
    end_game(myInfo);

}

void CLI::end_game(info_game myInfo) {

    clear();
 
    if(myInfo.winner){
        mvprintw(2, 6, "Bravo vous avez gagné ! ");
    }
    else{
         mvprintw(2, 6, "Dommage vous avez perdu! ");
    }

    mvprintw(5, 6, "Voici vos statistiques");
    mvprintw(8,6, "  * Score: ");mvprintw(8, 17,"%d",myInfo.score);
    mvprintw(9,6,"  * Level:"); mvprintw(9,17,"%d", myInfo.level);
    mvprintw(10,6,"  * Lignes complétées: "); mvprintw(10,31,"%d", myInfo.line_complete);

    mvprintw(20, 6, "Click sur une touche pour continuer ! ");

    refresh();
    getch();
    menu();

}


void CLI::menu() {

    clear();
    bool is_on_button = true;

    char *choices[] = { "PLAY GAME",
                        "CHAT",
                        "FRIENDS",
                        "STATS",
                        "SETTINGS",
                	    "EXIT"
                  };
    int n_choices = sizeof(choices) / sizeof(char *);
     

    WINDOW *menu_win;
    menu_win = newwin(24, 80, 0, 0);
    box(menu_win, 0, 0);
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

		      choice_game();
          break;}


        else if (choice == 2){
        	clear();
            chat();
            }


        else if (choice == 3){
        	clear();
          friends_manager->displayFriendsMenu();
          menu();
          break;

          }

        else if (choice == 4){
        	clear();
          statistics_manager->displayStatisticsMenu();
          menu();
          break;
          }

        else if (choice == 5){
        	clear();
        	SettingMenu * s = new SettingMenu();
          menu();
          break;
          }

        else if (choice == 6){
        	clear();
        	break;
            }

    }
    endwin();

	}



void CLI::choice_game() {

    clear();
    refresh();
    bool is_on_button = true;

    char *choices[] = { "Classic",
                        "Marathon",
                        "Sprint",
                        "VS",
                        "Power UP"
                  };
    int n_choices = sizeof(choices) / sizeof(char *);
    
    //initscr();
    WINDOW *menu_choice_game;
    menu_choice_game = newwin(24, 80, 0, 0);
    noecho();    // On cache les inputs du terminal.
    curs_set(0); // On cac
    box(menu_choice_game, 0, 0);
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
        if (choice == 1){

            play(choice);
           break;
        }

        else if (choice == 2){

            play(choice);
            break;
        }

        else if (choice == 3){

            play(choice);
            break; }

          else if (choice == 4){

            play(choice);
            break;
        }
         else if (choice == 5){

            play(choice);
            break; }

    }

    }
