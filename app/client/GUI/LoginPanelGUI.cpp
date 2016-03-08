#include "LoginPanelGUI.hpp"


void LoginPanelGUI::makeLogin() {
    const char* pseudo = m_pseudo->text().toStdString().c_str();
    const char* mdp = m_pseudo->text().toStdString().c_str();
    PacketManager::makeLoginRequest(pseudo, mdp);
}

void LoginPanelGUI::printLoginResult(std::string message) {
    QString msg = QString::fromUtf8(message.c_str());
    emit mustPrintResult(msg);
}

LoginPanelGUI::LoginPanelGUI() : QWidget() {
    setFixedSize(600,350);

    QPixmap pixmap("background.jpg");
    pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, pixmap);
    setPalette(palette);

    QFont policeTitre("Comic Sans MS",50,99,true);

    gridlayout = new QGridLayout(this);

    title= new QLabel("Wizard Poker");
    title->setFont(policeTitre);
    title->setAlignment(Qt::AlignHCenter);

    m_pseudo= new QLineEdit;
    m_mdp= new QLineEdit;
    m_mdp->setEchoMode(QLineEdit::Password);

    pseudo= new QLabel("Pseudo :");
    mdp= new QLabel("Mot de passe :");

    gridlayout->addWidget(title,1,1,1,2);
    gridlayout->addWidget(pseudo,2,1);
    gridlayout->addWidget(m_pseudo,2,2);
    gridlayout->addWidget(mdp,3,1);
    gridlayout->addWidget(m_mdp,3,2);

    login = new QPushButton("Login", this);
    signIn = new QPushButton("S'enregistrer", this);

    QFont maPolice("Comic Sans MS",20,85,false); //type,taille,epaisseur,italique
    login->setFont(maPolice);
    signIn->setFont(maPolice);

    layout= new QHBoxLayout;
    layout->addWidget(login);
    layout->addWidget(signIn);

    gridlayout->addLayout(layout,4,1,1,2);


    gridlayout->setColumnStretch(0, 1);
    gridlayout->setColumnStretch(1, 2);
    gridlayout->setColumnStretch(2, 2);
    gridlayout->setColumnStretch(3, 1);

    gridlayout->setRowStretch(0, 1);
    gridlayout->setRowStretch(1, 3);
    gridlayout->setRowStretch(2, 2);
    gridlayout->setRowStretch(3, 2);
    gridlayout->setRowStretch(4, 2);
    gridlayout->setRowStretch(5, 1);

    QObject::connect(login, SIGNAL(clicked()), this, SLOT(makeLogin()));
    QObject::connect(this, SIGNAL(mustPrintResult(QString)), this, SLOT(loginDisplayResult(QString)));
}

void LoginPanelGUI::loginDisplayResult(const QString message) {
    const QString titre = "Erreur";
    QMessageBox::information(this, titre, message);
}


LoginPanelGUI::~LoginPanelGUI() {
    delete pseudo;
    delete mdp;
    delete title;
//    delete beginSpace;
//    delete endSpace;
    delete gridlayout;
    delete m_pseudo;
    delete m_mdp;
    delete layout;
    delete login;
    delete signIn;
}

