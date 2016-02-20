#include "LoginPanel.hpp"

LoginPanel::LoginPanel() : isWainting(false) {
    /* Initialize field and set some options
     * <height> <width> <toprow> <leftcol> <offscreen> <nbuffers>
     */
    field[0] = new_field(1, 31, 4, 24, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);  /* Don't go to the next field when full */
    field[1] = new_field(1, 31, 6, 24, 0, 0);
    field_opts_off(field[1], O_AUTOSKIP);
    //field_opts_off(field[1], O_PUBLIC); /* Don't display password character */
    
    /* Create the form and calculate size needed */
    int rows, cols;
    form = new_form(field);
    scale_form(form, &rows, &cols);
    
    /* Create a window and put form in it */
    win = newwin(rows + 6, cols + 8, 0, 6);
    keypad(win, TRUE);
    set_form_win(form, win);
    
    /* Post form and refresh window */
    post_form(form);
    wrefresh(win);
    
    /* Add some label */
    mvprintw(2, 10, DEFAULT_LABEL);
    mvprintw(4, 10, "Pseudo       :");
    mvprintw(6, 10, "Mot de passe :");
    mvprintw(8, 10, "(Utilisez les flèches pour changer de champs)");
    mvprintw(10, 10, "F1: Annuler     F2: Se connecter     F3: S'enregistrer");
}

LoginPanel::~LoginPanel() {
    /* We must remove the form and clear field before exiting */
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    free_field(field[1]);
}

void LoginPanel::setFocus() {
    /* Set focus on the fist field and move cursor to it */
    set_current_field(form, field[0]);
    move(4, 24);
    refresh();
}

void LoginPanel::proceed(bool registration) {
    /* Get the pseudo from the first field */
    char *pseudo = field_buffer(field[0], 0);
    
    /*TODO (why empty ?) Get the password from the second field */
    char *password = field_buffer(field[1], 0);
    
    if (registration) {
        printWait(REGISTRATION_IN_PROGRESS);
        CommService::makeRegistrationRequest(pseudo, password);
    } else {
        printWait(LOGIN_IN_PROGRESS);
        CommService::makeLoginRequest(pseudo, password);
    }
}

void LoginPanel::printWait(std::string message) {
    isWainting = true;
    attron(COLOR_PAIR(2));
    mvprintw(2, 10, (char*)message.c_str());
    attroff(COLOR_PAIR(2));
    refresh();
    
    while(isWainting);
}

/* Ask user login informations
 * Also provides button to login or register
 */
void LoginPanel::askLogin() {
    /* Define work variable using for verification and beep */
    int indexA = 0;
    int sizeA = 0;
    int indexB = 0;
    int sizeB = 0;
    bool passwordForm = false; /* false: pseudo | true: password */
    
    /* Set focus on the fist form */
    setFocus();
    
    /* Loop through to get user requests */
    while((input = getch())) {
        switch(input) {
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
                if ((!passwordForm && (indexA == 0 || sizeA == 0)) ||
                    (passwordForm && (indexB == 0 || sizeB == 0))) {
                    beep();
                } else {
                    form_driver(form,REQ_LEFT_CHAR);
                    if (passwordForm) {
                        indexB -= 1;
                    } else {
                        indexA -= 1;
                    }
                }
                break;
            case KEY_RIGHT:
                /* Go to the next character (if available) */
                if ((!passwordForm && (indexA == sizeA || sizeA == 0)) ||
                    (passwordForm && (indexB == sizeB || sizeB == 0))) {
                    beep();
                } else {
                    form_driver(form,REQ_RIGHT_CHAR);
                    if (passwordForm) {
                        indexB += 1;
                    } else {
                        indexA += 1;
                    }
                }
                break;
            case KEY_BACKSPACE:
                /* Remove previous character (if available) */
                if ((!passwordForm && (indexA == 0 || sizeA == 0)) ||
                    (passwordForm && (indexB == 0 || sizeB == 0))) {
                    beep();
                } else {
                    form_driver(form,REQ_LEFT_CHAR); 
                    form_driver(form,REQ_DEL_CHAR);
                    if (passwordForm) {
                        indexB -= 1;
                        sizeB -= 1;
                    } else {
                        indexA -= 1;
                        sizeA -= 1;
                    }
                }
                break;
            case KEY_F(1):
                /* Clean all field and reset work variable */
                form_driver(form,REQ_CLR_FIELD);
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form,REQ_CLR_FIELD);
                indexA = 0;
                sizeA = 0;
                indexB = 0;
                sizeB = 0;
                passwordForm = false;
                setFocus();
                break;
            case KEY_F(2):
                proceed();
                return;
            case KEY_F(3):
                proceed(true);
                return;
            default:
                /* If it's the SPACEBAR, we beep */
                if (input == ' ') {
                    beep();
                } else if ((!passwordForm && sizeA == 30) ||
                    (passwordForm && sizeB == 30)) {
                    printError(MAX_SIZE_ERROR);
                    beep();
                } else {
                    /* Reset error and print character */
                    mvprintw(2, 10, DEFAULT_LABEL);
                    form_driver(form, input);
                    if (passwordForm) {
                        indexB += 1;
                        sizeB += 1;
                    } else {
                        indexA += 1;
                        sizeA += 1;
                    }
                }
                break;
        }
    }
}

/* Display and error message in red top of the fileds
 * Can be use for error like field empty or login error
 * @message : the string to display as an error
 */
void LoginPanel::printError(std::string message) {
    beep();
    attron(COLOR_PAIR(1));
    mvprintw(2, 10, (char*)message.c_str());
    attroff(COLOR_PAIR(1));
    setFocus();
    refresh();
}
