#include "LoginPanel.hpp"

LoginPanel::LoginPanel() {
    WizardLogger::info("Affichage du la demande de login");
    /* Initialize field and set some options
     * <height> <width> <toprow> <leftcol> <offscreen> <nbuffers>
     */
    field[0] = new_field(1, 30, 4, 24, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);  /* Don't go to the next field when full */
    field[1] = new_field(1, 30, 6, 24, 0, 0);
    field_opts_off(field[1], O_AUTOSKIP);
    
    /* Create the form and post it */
    form = new_form(field);
    post_form(form);
    
    /* Add some label */
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

/* Ask user login informations
 * Also provides button to login or register
 */
void LoginPanel::askLogin() {
    /* Loop through to get user requests */
    setFocus();
    while((input = getch())) {
        switch(input) {
            case KEY_DOWN:
                /* Go to the next field (at the end of the buffer) */
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_UP:
                /* Go to the previous field (at the end of the buffer) */
                form_driver(form, REQ_PREV_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_LEFT:
                /* Go to the previous character (if available) */
                form_driver(form,REQ_LEFT_CHAR);
                break;
            case KEY_RIGHT:
                /* Go to the next character (if available) */
                form_driver(form,REQ_RIGHT_CHAR);
                break;
            case KEY_BACKSPACE:
                /* Remove previous character (if available) */
                form_driver(form,REQ_LEFT_CHAR); 
                form_driver(form,REQ_DEL_CHAR);
                break;
            case KEY_F(1):
                /* Clean all field */
                form_driver(form,REQ_CLR_FIELD);
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form,REQ_CLR_FIELD);
                setFocus();
                break;
            case KEY_F(2):
                printError("   LOGIN NON IMPLEMENTE   ");
                break;
            case KEY_F(3):
                printError("INSCRIPTION NON IMPLEMENTE");
                break;
            default:
                /* If it's the SPACEBAR, we beep */
                if (input == ' ') {
                    beep();
                } else {
                    /* We reset error message before display input */
                    mvprintw(2, 10, "                          ");
                    form_driver(form, input);
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
}
