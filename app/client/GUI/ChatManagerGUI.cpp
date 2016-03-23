#include "ChatManagerGUI.hpp"

std::map<std::string,ChatWidget*> ChatManagerGUI::_listTab;
ChatManagerGUI* ChatManagerGUI::_instance;


ChatManagerGUI::ChatManagerGUI(QWidget* parent): QWidget(parent) {

    _layout = new QGridLayout(this);
    _tab = new QTabWidget(this);
    _friends= new QListWidget;

    _layout->addWidget(_tab,0,0);

    _tab->addTab(_friends,tr("General"));

    _friends->addItem("remy");     //A ENLEVER !!!!!!!
    _friends->addItem("detobel");  //A ENLEVER !!!!!!!
    _friends->addItem("carlos");   //A ENLEVER !!!!!!!
    _friends->addItem("corentin"); //A ENLEVER !!!!!!!
    _friends->addItem("raphael");  //A ENLEVER !!!!!!!
    _friends->addItem("amin");     //A ENLEVER !!!!!!!
    _friends->addItem("max");      //A ENLEVER !!!!!!!



    /*
     * for (int i = 0; i<sizeFriendList; i++){
     *  _friends->addItem(FriendList[i]);
     * }
    */


    _tab->setTabsClosable(true);
    connect(_tab, SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    _tab->tabBar()->tabButton(0,QTabBar::RightSide)->resize(0,0);

    connect(_friends, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(newTab(QListWidgetItem*)));
//    connect(this, SIGNAL(sigNewMessage(QString, QString, QString)),
//            this, SLOT(recvMessage(QString, QString, QString)));


    _instance = this;
}


/**
 * Call this function when reciev a new message
 *
 * @param playerFrom player who send message
 * @param playerTo player who reciev message
 * @param msg send message
 */
void ChatManagerGUI::reqNewMessage(std::string playerFrom, std::string playerTo, std::string msg) {


//    ChatWidget* chatWidget;
//    if(playerFrom.toStdString() == Player::getPlayer()->getName()) {
//        chatWidget = getChatWidget(playerTo.toStdString());
//    } else {
//        chatWidget = getChatWidget(playerFrom.toStdString());
//    }


    emit sigNewMessage(QString(playerFrom.c_str()), QString(playerTo.c_str()), QString(msg.c_str()));
}

void ChatManagerGUI::closeTab(int i){
    QString Qstr = _tab->tabText(i);
    std::map<std::string,ChatWidget*>::iterator it = _listTab.find(Qstr.toStdString());
    if(it != _listTab.end()) {
        _listTab.erase(it);
    } else {
        WizardLogger::warning("Impossible de trouver l'onglet à l'index: " +
                              std::to_string(i));
    }
    _tab->removeTab(i);
}

void ChatManagerGUI::newTab(QListWidgetItem* item){
    std::string pseudo = item->text().toStdString();
    if(_listTab.count(pseudo) == 0) {
        ChatWidget* chatWidget = new ChatWidget(pseudo, this);
        _tab->addTab(chatWidget, item->text());
        _listTab[pseudo] = chatWidget;

        connect(this, SIGNAL(sigNewMessage(QString, QString, QString)),
                chatWidget, SLOT(showNewMessage(QString, QString, QString)));
    } else {
        WizardLogger::info("Une fenêtre de tchat existe déjà avec " + pseudo);
    }
}

/**
 * Player reciev a new message
 *
 * @param playerFrom player who send message
 * @param playerTo player who reciev message
 * @param msg which is send
 */
void ChatManagerGUI::newMessage(QString playerFrom, QString playerTo,
                                QString msg) {

    ChatWidget* chatWidget;
    if(playerFrom.toStdString() == Player::getPlayer()->getName()) {
        chatWidget = getChatWidget(playerTo.toStdString());
    } else {
        chatWidget = getChatWidget(playerFrom.toStdString());
    }

    emit chatWidget->recvMessage(playerFrom, playerTo, msg);

}

/**
 * Search a ChatWidget whith the pseudo
 *
 * @param pseudo that we searsh
 * @return the ChatWidget or nullptr
 */
ChatWidget* ChatManagerGUI::getChatWidget(std::string pseudo) {
    ChatWidget* res = nullptr;
    std::map<std::string,ChatWidget*>::iterator it = _listTab.find(pseudo);
    if(it != _listTab.end()) {
        res = it->second;
    }
    return res;
}

