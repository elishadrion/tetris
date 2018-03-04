#include "SalonChat.hpp"
extern SalonChat* salon_chat;

char* SalonChat::trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}

void SalonChat::chatReceiver(char* message, char* sender){
    char ttime[10];
    
    struct tm *akttime;
    time_t second;
    time(&second);
    
    akttime = localtime(&second);
    strftime(ttime, 10, "%H:%M:%S", akttime);
    wprintw(msg_win_chat, "<%s> %s : %s\n", ttime, sender, message);
    wrefresh(msg_win_chat);
    
}

void SalonChat::print_online_users_chat(char* users,WINDOW *win){
	size_t taille = strlen(users);
	char tmp[7];
	strncpy(tmp,"",8);
	int j = 0;
	int line = 1;

	for (int i=0; i < taille; i++){
		if(users[i] != ','){
			if (j<8){
				tmp[j] = users[i];
				j++;
			}
		}
		else{
			mvwprintw(win,line,1,"%s",tmp);
			strncpy(tmp,"",8);
			j=0;
			line++;
		}
	}
	mvwprintw(win,line,1,"%s",tmp);
	wrefresh(win);
}

void SalonChat::startChat(){
	pthread_t rec;
	FIELD *field[1];
	FORM  *form;
	int ch;
	int MAX_FIELD = 126;
	char inputstring[MAX_FIELD], ttime[10], tester[156];
	
	initscr();
	keypad(stdscr, TRUE);

	msg_win_chat = newwin(20, 70, 0, 0);
	user_win = newwin(20, 10, 0, 70);
	input_win = newwin(4, 80, 20, 0);
	box(user_win, 0, 0);
	box(input_win, 0, 0);

	scrollok(msg_win_chat, TRUE);
	
	wrefresh(msg_win_chat);
	wrefresh(user_win);

	field[0] = new_field(2, 78, 0, 0, 0, 0);
	field[1] = NULL;
	
	form = new_form(field);
    keypad(input_win, TRUE);
    set_form_win(form, input_win);
    set_form_sub(form, derwin(input_win, 2, 78, 1, 1));
	post_form(form);
	pos_form_cursor(form);

	field_opts_off(field[0], O_STATIC);
	set_max_field(field[0], MAX_FIELD);

	wrefresh(input_win);

	form_driver(form, REQ_VALIDATION);
	/*char* bidon pour tester un buffer vide */
	snprintf(tester, MAX_FIELD, "%s", trim_whitespaces(field_buffer(field[0], 0)));

	//pthread_create(&rec, NULL, chatReceiver, NULL);
	SalonChat::print_online_users_chat("Abderr,TomyLeBg,EimanRat,ElishETH,AlexKGB",user_win);
	while((ch = wgetch(input_win)) != KEY_F(1))
	{	switch(ch)
		{
			case 10:
				form_driver(form, REQ_VALIDATION);
				snprintf(inputstring, MAX_FIELD, "%s", trim_whitespaces(field_buffer(field[0], 0)));
				
				if (strcmp(inputstring,tester) != 0) //Pour pas send des messages vide
				{
	                PacketManager::send_chat_message(username,inputstring);
                    set_field_buffer(field[0], 0, "");
            	}
            	break;

			case KEY_LEFT:
				form_driver(form, REQ_PREV_CHAR);
				break;

			case KEY_RIGHT:
				form_driver(form, REQ_NEXT_CHAR);
				break;

            case KEY_BACKSPACE:
				form_driver(form, REQ_DEL_PREV);
				break;

			case KEY_DC:
				form_driver(form, REQ_DEL_CHAR);
				break;

			case 27: //ESC
				//send exit
				break;

			default:
				form_driver(form, ch);
				form_driver(form, REQ_DEL_CHAR);
				break;
		}
	}

	/* Unpost form and free the memory */
	unpost_form(form);
	free_form(form);
	free_field(field[0]);
	free_field(field[1]); 
	endwin();
}

