#include "LoginPanel.hpp"

LoginPanel::LoginPanel(WINDOW *mainWindow) {
    /* Create the panel (these is visible by default) */
    WizardLogger::info("Création du panel de login");
    panel = new_panel(mainWindow);
        
    /* Initialize field and set some options
     * <height> <width> <toprow> <leftcol> <offscreen> <nbuffers>
     */
    field[0] = new_field(1, 20, 4, 24, 0, 0);
    field_opts_off(field[0], O_AUTOSKIP);  /* Don't go to the next field when full */
    field[1] = new_field(1, 20, 6, 24, 0, 0);
    field_opts_off(field[1], O_AUTOSKIP);
    field_opts_off(field[1], O_PUBLIC); /* Don't display text for password field */
    
    /* Create the form and post it on the panel */
    form = new_form(field);
    post_form(form);
    
    /* Add some label */
    mvprintw(4, 10, "Pseudo       :");
    mvprintw(6, 10, "Mot de passe :");
    mvprintw(8, 10, "(Utilisez les flèches pour changer de champs)");
    mvprintw(10, 10, "F1: Annuler     F2: Se connecter     F3: S'enregistrer");
    refresh();
}

LoginPanel::~LoginPanel() {
    /* We must remove the form and clear field before exiting */
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    free_field(field[1]);
}

/* Ask user login informations
 * Also provides button to login or register
 */
void LoginPanel::askLogin() {
    /* Set focus on the fist field and move cursor to it */
    set_current_field(form, field[0]);
    move(4, 20);
    refresh();
    
    /* Loop through to get user requests */
    while((input = getch())) {
        switch(input) {
            case KEY_DOWN:
                /* Go to next field (at the end of the buffer) */
                form_driver(form, REQ_NEXT_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_UP:
                /* Go to previous field (at the end of the buffer) */
                form_driver(form, REQ_PREV_FIELD);
                form_driver(form, REQ_END_LINE);
                break;
            case KEY_BACKSPACE:
                /* Remove previous character */
                form_driver(form,REQ_LEFT_CHAR); 
                form_driver(form,REQ_DEL_CHAR);
            case KEY_F(1):
                printError("ANNULATION NON IMPLEMENTE");
            case KEY_F(2):
                printError("LOGIN NON IMPLEMENTE");
            case KEY_F(3):
                printError("INSCRIPTION NON IMPLEMENTE");
            default:
                /* We print it */    
                form_driver(form, input);
                break;
        }
    }
}

/* Display and error message in red top of the fileds
 * Can be use for error like field empty or login error
 * @message : the string to display as an error
 */
void LoginPanel::printError(std::string message) {
    attron(COLOR_PAIR(1));
    mvprintw(2, 10, (char*)message.c_str());
    attroff(COLOR_PAIR(1));
    askLogin();
}

/* Change the visibility of the current panel
 * And update CLI just after
 * @visibility : if true, display panel
 */
void LoginPanel::setVisibility(bool visibility) {
    if(visibility) {
        WizardLogger::info("Affichage du panel de login");
        show_panel(panel);
        top_panel(panel);
    } else {
        WizardLogger::info("Masquage du panel de login");
        hide_panel(panel);
    }
    update_panels();
    doupdate();
}
