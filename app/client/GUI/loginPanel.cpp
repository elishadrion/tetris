#include "loginPanel.h"

LoginPanel::LoginPanel() : QWidget()
{
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

    //beginSpace= new QLabel("\t");
    //endSpace= new QLabel("\t");

    gridlayout->addWidget(title,1,1,1,2);
    //gridlayout->addWidget(beginSpace,1,0);
    gridlayout->addWidget(pseudo,2,1);
    gridlayout->addWidget(m_pseudo,2,2);
    //gridlayout->addWidget(endSpace,1,3);
    gridlayout->addWidget(mdp,3,1);
    gridlayout->addWidget(m_mdp,3,2);

    login = new QPushButton("Login");
    signIn = new QPushButton("S'enregistrer");

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

}
