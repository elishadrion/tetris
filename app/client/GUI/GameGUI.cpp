//#include "GameGUI.hpp"

//GameGUI::GameGUI() : QWidget() {

//    gridlayout = new QGridLayout(this);

//    QString strLabel;
//    QLabel* label;

//    // Cartes en main adverses face cachée
//    for(unsigned i = 0; i < 7; ++i) {
//        QHBoxLayout* carteAdv= new QHBoxLayout(this);
//        strLabel = ("test: " + i);
//        label = new QLabel(strLabel);
//        label->setStyleSheet("background-color: red");
//        carteAdv->addWidget(label);
//        gridlayout->addLayout(carteAdv, 0, 3+i);
//        gridlayout->setColumnStretch(3+i, 2);
//    }


//    // Cartes posée adverse
//    for(unsigned i = 0; i < 7; ++i) {
//        QHBoxLayout* advPlaceCarte = new QHBoxLayout(this);
//        strLabel = ("test2: " + i);
//        label = new QLabel(strLabel);
//        label->setStyleSheet("background-color: lightblue");
//        advPlaceCarte->addWidget(label);
//        gridlayout->addLayout(advPlaceCarte, 2, 3+i);
//        //gridlayout->setColumnStretch(3+i, 2);
//    }

//    // Deck Adverse
//    QHBoxLayout* advDeckAdv = new QHBoxLayout(this);
//    strLabel = ("Deck A");
//    label = new QLabel(strLabel);
//    label->setStyleSheet("background-color: gray");
//    advDeckAdv->addWidget(label);
//    gridlayout->addLayout(advDeckAdv, 2, 1);


//    // Deck
//    QHBoxLayout* advDeck = new QHBoxLayout(this);
//    strLabel = ("Deck");
//    label = new QLabel(strLabel);
//    label->setStyleSheet("background-color: gray");
//    advDeck->addWidget(label);
//    gridlayout->addLayout(advDeck, 4, 1);


//    // Cartes en main
//    for(unsigned i = 0; i < 7; ++i) {
//        QHBoxLayout* carteInHand;
//        carteInHand= new QHBoxLayout(this);
//        strLabel = ("test2: " + i);
//        label = new QLabel(strLabel);
//        label->setStyleSheet("background-color: green");
//        carteInHand->addWidget(label);
//        gridlayout->addLayout(carteInHand, 6, 3+i);
//        //gridlayout->setColumnStretch(3+i, 2);
//    }


//    // Cartes posée
//    for(unsigned i = 0; i < 7; ++i) {
//        QHBoxLayout* placeCarte;
//        placeCarte = new QHBoxLayout(this);
//        strLabel = ("test2: " + i);
//        label = new QLabel(strLabel);
//        label->setStyleSheet("background-color: blue");
//        placeCarte->addWidget(label);
//        gridlayout->addLayout(placeCarte, 4, 3+i);
//        //gridlayout->setColumnStretch(3+i, 2);
//    }


//    // Passer
//    QPushButton *m_bouton = new QPushButton("Passer \nson tour", this);
//    gridlayout->addWidget(m_bouton, 3, 11);


//    // Tchat
////    QTabWidget* tChat = new QTabWidget(this);
////    QGroupBox* tChatOnglet = new QGroupBox(this);
////    strLabel = ("Tchat");
////    label = new QLabel(strLabel);
////    label->setStyleSheet("background-color: yellow");
////    tChatOnglet->addWidget(label, 6);
////    QTextEdit* textBox = new QTextEdit(this);
////    tChatOnglet->addWidget(textBox);
////    tChat->addTab(tChatOnglet, "test");
////    //gridlayout->addLayout(tChat, 0, 13, 6, 3);
////    gridlayout->addWidget(tChat, 0, 13, 6, 3);

////    // Tchat
//    QVBoxLayout* tChat = new QVBoxLayout(this);
//    strLabel = ("Tchat");
//    label = new QLabel(strLabel);
//    label->setStyleSheet("background-color: yellow");
//    tChat->addWidget(label, 6);
//    QTextEdit* textBox = new QTextEdit(this);
//    tChat->addWidget(textBox);
//    gridlayout->addLayout(tChat, 0, 13, 6, 3);

//    // PUB
//    QHBoxLayout* pub = new QHBoxLayout(this);
//    strLabel = ("PUB");
//    label = new QLabel(strLabel);
//    label->setStyleSheet("background-color: black; color: white;");
//    pub->addWidget(label);
//    gridlayout->addLayout(pub, 6, 13, 1, 3);


//    // colonne de gauche
//    gridlayout->setColumnStretch(0, 1);
//    gridlayout->setColumnStretch(1, 1);
//    gridlayout->setColumnStretch(2, 1);

//    // colonne de droite
//    gridlayout->setColumnStretch(10, 1);
//    gridlayout->setColumnStretch(11, 1);
//    gridlayout->setColumnStretch(12, 1);

//    gridlayout->setColumnStretch(13, 2); // tchat
//    gridlayout->setColumnStretch(14, 2); // tchat
//    gridlayout->setColumnStretch(15, 2); // tchat


//    // Ligne des cartes 1
//    gridlayout->setRowStretch(0, 3);
//    gridlayout->setRowStretch(1, 1);
//    gridlayout->setRowStretch(2, 3);
//    gridlayout->setRowStretch(3, 2); // bouton passer
//    gridlayout->setRowStretch(4, 3);
//    gridlayout->setRowStretch(5, 1);
//    gridlayout->setRowStretch(6, 3);




//    /*
//    m_pseudo= new QLineEdit;
//    m_mdp= new QLineEdit;
//    m_mdp->setEchoMode(QLineEdit::Password);

//    pseudo= new QLabel("Pseudo :");
//    mdp= new QLabel("Mot de passe :");

//    //beginSpace= new QLabel("\t");
//    //endSpace= new QLabel("\t");

//    gridlayout->addWidget(title,1,1,1,2);
//    //gridlayout->addWidget(beginSpace,1,0);
//    gridlayout->addWidget(pseudo,2,1);
//    gridlayout->addWidget(m_pseudo,2,2);
//    //gridlayout->addWidget(endSpace,1,3);
//    gridlayout->addWidget(mdp,3,1);
//    gridlayout->addWidget(m_mdp,3,2);


//    login = new QPushButton("Login");
//    signIn = new QPushButton("S'enregistrer");

//    QFont maPolice("Comic Sans MS",20,85,false); //type,taille,epaisseur,italique
//    login->setFont(maPolice);
//    signIn->setFonQHBoxLayoutt(maPolice);

//    layout= new QHBoxLayout;
//    layout->addWidget(login);
//    layout->addWidget(signIn);

//    gridlayout->addLayout(layout,4,1,1,2);

//    gridlayout->setColumnStretch(0, 1);
//    gridlayout->setColumnStretch(1, 2);
//    gridlayout->setColumnStretch(2, 2);
//    gridlayout->setColumnStretch(3, 1);

//    gridlayout->setRowStretch(0, 1);
//    gridlayout->setRowStretch(1, 3);
//    gridlayout->setRowStretch(2, 2);
//    gridlayout->setRowStretch(3, 2);
//    gridlayout->setRowStretch(4, 2);
//    gridlayout->setRowStretch(5, 1);
//    */

//    this->showMaximized(); // set full screen

//}
