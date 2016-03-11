#include "LoginPanelGUI.hpp"


/**
 * Constructor
 */
LoginPanelGUI::LoginPanelGUI() : QWidget() {
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
    QObject::connect(this, SIGNAL(mustPrintResult(QString)), this, SLOT(loginDisplayResult(QString)));
    QObject::connect(this, SIGNAL(mustDisplayMainMenu()), this, SLOT(displayMainMenu()));


    QObject::connect(_m_pseudo, SIGNAL(textChanged(QString)), this, SLOT(setStrPseudo(QString)));
    QObject::connect(_m_mdp, SIGNAL(textChanged(QString)), this, SLOT(setStrMdp(QString)));
}


/**
 * Call the mustPrintResult (emit)
 * @param message which must be print
 */
void LoginPanelGUI::callPrintLoginResult(std::string message) {
    QString msg = QString::fromUtf8(message.c_str());
    emit mustPrintResult(msg);
}


/**
 * Call the mustDisplayMainMenu (emit)
 */
void LoginPanelGUI::callDisplayMainMenu() {
    emit mustDisplayMainMenu();
}


/**
 * Display the login result
 *
 * @param message to display
 */
void LoginPanelGUI::loginDisplayResult(const QString message) {
    const QString titre = "Erreur";
    QMessageBox::critical(this, titre, message);
}


/**
 * Make login request
 */
void LoginPanelGUI::makeLogin() {
    const char* pseudo = _strPseudo.c_str();
    const char* mdp = _strMdp.c_str();
    PacketManager::makeLoginRequest(pseudo, mdp);
}


/**
 * Make register request
 */
void LoginPanelGUI::makeRegister() {
    const char* pseudo = _strPseudo.c_str();
    const char* mdp = _strMdp.c_str();
    PacketManager::makeRegistrationRequest(pseudo, mdp);
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
    new MenuPanelGUI();
    close();
}

