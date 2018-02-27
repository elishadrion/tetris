

#include <thread>
#include "Login_CLI.hpp"



Login_CLI::Login_CLI(): my_form(nullptr){

    /* Initialize curses */
    
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    field[0] = new_field(1, 10, 4, 18, 0, 0);
    field[1] = new_field(1, 10, 6, 18, 0, 0);

    window();

    

}

Login_CLI::~Login_CLI(){

    endwin();
      unpost_form(my_form);
    // free_form(my_form);
    free_field(field[0]);
    free_field(field[1]);
     

}


void Login_CLI::window(){

    /* Initialize few color pairs */
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    /* Initialize the fields */
    
    

    /* Set field options */
    set_field_fore(field[0], COLOR_PAIR(1));/* Put the field with blue background */
    set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
                        /* are printed in white     */
    field_opts_off(field[0], O_AUTOSKIP);   /* Don't go to next field when this */
                        /* Field is filled up       */

    set_field_fore(field[1], COLOR_PAIR(3));
    set_field_back(field[1], A_UNDERLINE); 
    field_opts_off(field[1], O_AUTOSKIP);

    /* Create the form and post it */
    my_form = new_form(field);
    post_form(my_form);
    refresh();
    
    set_current_field(my_form, field[0]); /* Set focus to the colored field */
    mvprintw(4, 10, "Value 1:");
    mvprintw(6, 10, "Value 2:");
    mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys to switch between fields");
    refresh();



}



void Login_CLI::try_login() {

    
    pthread_mutex_lock(&info->packetStackMutex);
    
    int ch;
    int index_pseudo=0;
    int index_password=0;
    int len_pseudo=0;
    int len_password=0;
    int is_pseudo = 1;        

    /* Loop through to get user requests */
    bool flag = false;
    while((ch = getch()) and not(flag))
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
                    index_password-=1;
                    len_password-=1;
                }
                break;
            case 10:
            form_driver(my_form, REQ_VALIDATION);
                flag = true;
                break;


            default:
                /* If this is a normal character, it gets */
                /* Printed                */    
                form_driver(my_form, ch);
                if(is_pseudo){
                    index_pseudo+=1;
                    len_pseudo+=1;
                }

                else{
                    index_password+=1;
                    len_password+=1;
                }
                break;
        }


}

    pseudo = empty_space_string(field_buffer(field[0], 0), len_pseudo);
    password = empty_space_string(field_buffer(field[1], 0), len_password);

}


bool Login_CLI::connect(){   
    
    try_login();
    bool success = false;

    PacketManager::send_login_request(pseudo.c_str(), password.c_str());
    
    /* Wait for result */

    

    pthread_cond_wait(&info->packetStackCond, &info->packetStackMutex);
    
    /* Check result */
     
    if (info->packetStack.empty()) {
        WizardLogger::info("Login réussi");
        success = true;
        
        
        //pthread_cond_wait(&packetStackCond, &packetStackMutex);
    } else {
        
        info->packetStack.pop_back();
    }
   
    /* Unlock */
    pthread_mutex_unlock(&info->packetStackMutex);
       
    


    return success;
        


}


void Login_CLI::play() {
    
	PacketManager::send_play_request();
    //Attend que la room soit complète pour lancer une partie VS
    pthread_cond_wait(&info->packetStackCond, &info->packetStackMutex);
    pthread_cond_wait(&info->packetStackCond, &info->packetStackMutex);


    //manager->create_game();
    


}











std::string Login_CLI::empty_space_string(const char*str, int len ){

    char c[len];
    for(int i=0; i<len;i++){

        c[i] = str[i];


    }

   std::string v(c);

   
    
    
    return v;
}
