#include "LoginPanel.hpp"

LoginPanel::LoginPanel() : isWainting(false), success(false) {
    /* Initialize field and set some options
     * LabelField - PseudoField - LabelField2 - PasswordField
     * <height> <width> <toprow> <leftcol> <offscreen> <nbuffers>
     */
    field[0] = new_field(1, 18, 1, 2, 0, 0); /* Label field 1 */
    field_opts_off(field[0], O_ACTIVE); /* Not visited during process */
    field_opts_off(field[0], O_AUTOSKIP);  /* Don't go to the next field when full */
    field[1] = new_field(1, 31, 1, 20, 0, 0); /* Pseudo field */
    field_opts_off(field[1], O_AUTOSKIP);
    set_field_back(field[1], A_UNDERLINE); /* Draw an line under field */
    field[2] = new_field(1, 18, 3, 2, 0, 0); /* Label field 2 */
    field_opts_off(field[2], O_ACTIVE);
    field_opts_off(field[2], O_AUTOSKIP);
    field[3] = new_field(1, 31, 3, 20, 0, 0); /* Pseudo field */
    field_opts_off(field[3], O_AUTOSKIP);
    field_opts_off(field[3], O_PUBLIC); /* Don't display password character */
    set_field_back(field[3], A_UNDERLINE);
    
    /* Create the form and calculate size needed */
    int rows;
    form = new_form(field);
    scale_form(form, &rows, &colsForm);

	/* Create the window to be associated with the form */
    window = newwin(rows+10, colsForm+10, 4, 4);
    keypad(window, TRUE);

	/* Set main window and sub window */
    set_form_win(form, window);
    set_form_sub(form, derwin(window, rows, colsForm, 2, 2));

	/* Print a border around the main window and print a title */
    box(window, 0, 0);
	printInMiddle(DEFAULT_LABEL, COLOR_PAIR(7));
    
    /* Add some label */
    set_field_buffer(field[0], 0, "Pseudo       :");
    set_field_buffer(field[2], 0, "Mot de passe :");
    mvwprintw(window, 8, 4, "(Utilisez les flèches pour changer de champs)");
    mvwprintw(window, 10, 4, "F1: Annuler     F2: Se connecter     F3: S'enregistrer");
    refresh();
}

LoginPanel::~LoginPanel() {
    /* We must remove the form and clear field before exiting */
    unpost_form(form);
	free_form(form);
	free_field(field[0]);
	free_field(field[1]);
	free_field(field[2]);
	free_field(field[3]);
}

void LoginPanel::show() {
    /* Post form */
    post_form(form);
}

void LoginPanel::hide() {
    /* Remove form */
    unpost_form(form);
}

/* Ask user login/registration informations */
void LoginPanel::focus() {
    /* Ensure that buffer is clean */
    form_driver(form, REQ_CLR_FIELD);
    form_driver(form, REQ_NEXT_FIELD);
    form_driver(form, REQ_CLR_FIELD);
    
    /* false: pseudo | true: password */
    bool passwordForm = false;
    
    /* Set focus on the pseudo field */
    setFocusToField();

    /* Loop through to get user requests */
    int input;
    while(!success) {
        switch(input = wgetch(window)) {
            case KEY_DOWN:
                /* Go to the next field (at the end of the buffer) */
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form, REQ_END_LINE);
                passwordForm = !passwordForm;
                break;
            case KEY_UP:
                /* Go to the previous field (at the end of the buffer) */
                form_driver(form, REQ_PREV_FIELD);
                form_driver(form, REQ_END_LINE);
                passwordForm = !passwordForm;
                break;
            case KEY_LEFT:
                /* Go to the previous character (if available) */
                if ((!passwordForm && (indexPseudo == 0 || sizePseudo == 0)) ||
                    (passwordForm && (indexPassword == 0 || sizePassword == 0))) {
                    beep();
                    form_driver(form, REQ_BEG_LINE);
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    if (passwordForm) {
                        indexPassword -= 1;
                    } else {
                        indexPseudo -= 1;
                    }
                }
                break;
            case KEY_RIGHT:
                /* Go to the next character (if available) */
                if ((!passwordForm && (indexPseudo == sizePseudo || sizePseudo == 0)) ||
                    (passwordForm && (indexPassword == sizePassword || sizePassword == 0))) {
                    beep();
                    form_driver(form, REQ_END_LINE);
                } else {
                    form_driver(form, REQ_RIGHT_CHAR);
                    if (passwordForm) {
                        indexPassword += 1;
                    } else {
                        indexPseudo += 1;
                    }
                }
                break;
            case KEY_BACKSPACE:
                /* Remove previous character (if available) */
                if ((!passwordForm && (indexPseudo == 0 || sizePseudo == 0)) ||
                    (passwordForm && (indexPassword == 0 || sizePassword == 0))) {
                    beep();
                    form_driver(form, REQ_BEG_LINE);
                } else {
                    form_driver(form, REQ_LEFT_CHAR);
                    form_driver(form, REQ_DEL_CHAR);
                    if (passwordForm) {
                        indexPassword -= 1;
                        sizePassword -= 1;
                    } else {
                        indexPseudo -= 1;
                        sizePseudo -= 1;
                    }
                }
                break;
            case KEY_F(1):
                /* Clean all field and reset work variable */
                form_driver(form, REQ_CLR_FIELD);
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form, REQ_CLR_FIELD);
                indexPseudo = 0;
                sizePseudo = 0;
                indexPassword = 0;
                sizePassword = 0;
                passwordForm = false;
                setFocusToField();
                break;
            case KEY_F(2):
                proceed();
                break;
            case KEY_F(3):
                proceed(true);
                break;
            default:
                /* If it's the SPACEBAR, we beep */
                if (input == ' ') {
                    beep();
                    form_driver(form, REQ_END_LINE);
                } else if ((!passwordForm && sizePseudo == 30) ||
                    (passwordForm && sizePassword == 30)) {
                    beep();
                    printInMiddle(MAX_SIZE_ERROR, COLOR_PAIR(1));
                } else {
                    /* Print character */
                    printInMiddle(DEFAULT_LABEL, COLOR_PAIR(7));
                    form_driver(form, input);
                    if (passwordForm) {
                        indexPassword += 1;
                        sizePassword += 1;
                    } else {
                        indexPseudo += 1;
                        sizePseudo += 1;
                    }
                }
                break;
        }
        
        /* Don't forget to refresh */
        refresh();
    }
}

/* Display and error message in red top of the fileds
 * Can be use for error like field empty or login error
 * @message : the string to display as an error
 */
void LoginPanel::printError(std::string message) {
    beep();
    printInMiddle((char*)message.c_str(), COLOR_PAIR(1));
    setFocusToField();
    isWainting = false;
}

/* Close LoginPanel and set signal to open MainPanel */
void LoginPanel::valideLogin() {
    success = true;
    isWainting = false;
}

//========================PRIVATE=============================

void LoginPanel::printInMiddle(char *string, chtype color) {
    int length, width, x, y;
	float temp;
    
    /* Calculate central position for printing */
	width = colsForm+4;
	length = LABEL_LENGHT;
	temp = (width - length)/ 2;
	x = 1 + (int)temp;
	
	/* Active color and display message */
	wattron(window, color);
	mvwprintw(window, 0, x, "%s", string);
	wattroff(window, color);
	refresh();
}

void LoginPanel::setFocusToField() {
    /* Set focus on the field and move cursor to it */
    set_current_field(form, field[1]);
    form_driver(form, REQ_END_LINE);
    refresh();
}

void LoginPanel::printWait(char* message) {
    isWainting = true;
    printInMiddle(message, COLOR_PAIR(2));
    while(isWainting); /* Avoid current thread to stop and exit program */
}

void LoginPanel::proceed(bool registration) {
    /* Sync buffer */
    form_driver(form, REQ_VALIDATION);
    
    /* Get the pseudo from the first field */
    char *pseudo = field_buffer(field[1], 0);
    
    /* Get the password from the second field */
    char *password = field_buffer(field[3], 0);

    if (registration) {
        PacketManager::makeRegistrationRequest(pseudo, password);
        printWait(REGISTRATION_IN_PROGRESS);
    } else {
        PacketManager::makeLoginRequest(pseudo, password);
        printWait(LOGIN_IN_PROGRESS);
    }
}
