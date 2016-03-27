#include "FriendsPanelGUI.hpp"

FriendsPanelGUI::FriendsPanelGUI(MenuPanelGUI* menu) : QMainWindow(), _menu(menu) {

    setStyleSheet("QMainWindow { background-image: url(:/Images/ligue_justicie.jpg) 0 0 0 0 stretch stretch; "
                  "background-repeat: no-repeat; background-position: center center; } "
                  "QPushButton { background-color: white; } "
                  "QLabel { background-color: rgba(187, 187, 187, 0.72); }");

    setWindowTitle("Mes Amis");
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    _people = new QLabel("Nom du joueur");
    _people->setFixedHeight(30);

    _back =  new QPushButton("Retour");
    _back->setMaximumHeight(50);
    _back->setMaximumWidth(200);
    connect(_back, SIGNAL(clicked()), this, SLOT(makeClose()));

    _back =  new QPushButton("Ajouter ami");
    _back->setMaximumHeight(50);
    _back->setMaximumWidth(200);
    connect(_back, SIGNAL(clicked()), this, SLOT(addFriend()));

    QGridLayout* layoutOfLayout = new QGridLayout(centralWidget);
    layoutOfLayout -> addWidget(_back, 0, 0);
    layoutOfLayout -> addWidget(_people, 0, 1);
    friendPos++;

    showFriends(layoutOfLayout);
    showMaximized();

}

void FriendsPanelGUI::makeClose() {
    _menu -> makeOpen();
    this -> close();
}

void FriendsPanelGUI::addFriend() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ajouter un ami"),
                                         tr("Pseudo du joueur:"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);
    // if (ok && !text.isEmpty()) {
    // 	char toChar[MAX_PSEUDO_SIZE];
    // 	for (size_t i = 0; i < text.size(); i++) {

    // 	}

	//PacketManager::makeFriendRequest();
    }
}

void FriendsPanelGUI::showFriends(QGridLayout* grid) {
    for (int i = 0; i < MAX_FRIENDS; i++) {
	QLabel * friendNameLabel = new QLabel(QString::fromStdString(Player::getPlayer() -> getFriends()[i]));
	friendNameLabel -> setFixedHeight(20);
	grid -> addWidget(friendNameLabel, friendPos, 0);
	if (friendNameLabel -> text() != "") {
	    QPushButton * friendDeleteButton = new QPushButton("Delete");
	    friendDeleteButton -> setMaximumWidth(50);
	    grid -> addWidget(friendDeleteButton, friendPos, 1);
	}
	friendPos++;
    }

}
