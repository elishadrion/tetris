#include "LoginPanelGUI.hpp"


/**
 * Constructor
 */
LoginPanelGUI::LoginPanelGUI(GUI* parent) : QWidget() {
    _gui = parent;

    setFixedSize(600,350);

    //QPixmap pixmap("background.jpg");
    //pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
    //QPalette palette;
    //palette.setBrush(QPalette::Background, pixmap);
    //setPalette(palette);

    QFont policeTitre("Comic Sans MS",50,99,true);

    _gridlayout = new QGridLayout(this);

    _title= new QLabel("Wizard Poker");
    _title->setFont(policeTitre);
    _title->setAlignment(Qt::AlignHCenter);

    _m_pseudo= new QLineEdit(this);
    _m_mdp= new QLineEdit(this);
    _m_mdp->setEchoMode(QLineEdit::Password);

    _pseudo= new QLabel("Pseudo :");
    _mdp= new QLabel("Mot de passe :");

    _gridlayout->addWidget(_title,1,1,1,2);
    _gridlayout->addWidget(_pseudo,2,1);
    _gridlayout->addWidget(_m_pseudo,2,2);
    _gridlayout->addWidget(_mdp,3,1);
    _gridlayout->addWidget(_m_mdp,3,2);

    _login = new QPushButton("Login", this);
    _signIn = new QPushButton("S'enregistrer", this);

    QFont maPolice("Comic Sans MS",20,85,false); //type,taille,epaisseur,italique
    _login->setFont(maPolice);
    _signIn->setFont(maPolice);

    _layout= new QHBoxLayout();
    _layout->addWidget(_login);
    _layout->addWidget(_signIn);

    _gridlayout->addLayout(_layout,4,1,1,2);


    _gridlayout->setColumnStretch(0, 1);
    _gridlayout->setColumnStretch(1, 2);
    _gridlayout->setColumnStretch(2, 2);
    _gridlayout->setColumnStretch(3, 1);

    _gridlayout->setRowStretch(0, 1);
    _gridlayout->setRowStretch(1, 3);
    _gridlayout->setRowStretch(2, 2);
    _gridlayout->setRowStretch(3, 2);
    _gridlayout->setRowStretch(4, 2);
    _gridlayout->setRowStretch(5, 1);

    QObject::connect(_login, SIGNAL(clicked()), this, SLOT(makeLogin()));
    QObject::connect(_signIn, SIGNAL(clicked()), this, SLOT(makeRegister()));


    QObject::connect(_m_pseudo, SIGNAL(textChanged(QString)), this, SLOT(setStrPseudo(QString)));
    QObject::connect(_m_mdp, SIGNAL(textChanged(QString)), this, SLOT(setStrMdp(QString)));
}

/**
 * Display the login result
 *
 * @param message to display
 */
void LoginPanelGUI::loginDisplayResult(const std::string message) {
    WizardLogger::info("Erreur Login: " + message);
    QMessageBox::critical(this, "Erreur", QString(message.c_str()));
}


/**
 * Make login request
 */
void LoginPanelGUI::makeLogin() {
    login(false);
}

/**
 * Make register request
 */
void LoginPanelGUI::makeRegister() {
    login(true);
}

/**
 * Process to make login
 *
 * @param newUser True if it's register (false if it's login)
 */
void LoginPanelGUI::login(bool newUser) {
    const char* pseudo = _strPseudo.c_str();
    const char* mdp = _strMdp.c_str();

    /* Lock */
    pthread_mutex_lock(&wizardDisplay->packetStackMutex);

    // Packet manager
    if(newUser) {
        PacketManager::makeRegistrationRequest(pseudo, mdp);
    } else {
        PacketManager::makeLoginRequest(pseudo, mdp);
    }

    /* Wait for result */
    pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);

    /* Check result */
    if (wizardDisplay->packetStack.empty()) {
        WizardLogger::info("Authentification réussi");
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Chargement des cartes en cours...");
        msgBox->show();

        /* Wait for result */
        pthread_cond_wait(&wizardDisplay->packetStackCond, &wizardDisplay->packetStackMutex);
        
        msgBox->hide();
        displayMainMenu();
    } else {
        loginDisplayResult(*reinterpret_cast<std::string*>(wizardDisplay->packetStack.back()));
        wizardDisplay->packetStack.pop_back();
    }

    /* Unlock */
    pthread_mutex_unlock(&wizardDisplay->packetStackMutex);

}



/**
 * Change the string pseudo
 *
 * @param qstr the new QString
 */
void LoginPanelGUI::setStrPseudo(QString qstr) {
    _strPseudo = qstr.toStdString();
}


/**
 * Change the string password
 *
 * @param qstr the new QString
 */
void LoginPanelGUI::setStrMdp(QString qstr) {
    _strMdp = qstr.toStdString();
}


/**
 * Display the main menu and close this
 */
void LoginPanelGUI::displayMainMenu() {
    _gui->setMainMenu(new MenuPanelGUI(_gui));
    close();
}

