#include "ChatManagerGUI.hpp"

std::vector<std::string> ChatManagerGUI::_listTab;
ChatManagerGUI* ChatManagerGUI::_instance;
std::mutex ChatManagerGUI::mtx;


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
    connect(this, SIGNAL(openNewTab(QString)), this, SLOT(newTab(QString)));

    _instance = this;
}


/**
 * Call this function when reciev a new message
 *
 * @param playerFrom player who send message
 * @param playerTo player who reciev message
 * @param msg send message
 */
void ChatManagerGUI::reqNewMessage(std::string playerFrom, std::string playerTo,
                                   std::string msg) {

    mtx.lock();
    emit openNewTab(QString(playerFrom.c_str()));
    mtx.lock();
    emit sigNewMessage(QString(playerFrom.c_str()), QString(playerTo.c_str()),
                       QString(msg.c_str()));
    mtx.unlock();
}

void ChatManagerGUI::closeTab(int i){
    QString Qstr = _tab->tabText(i);
    std::vector<std::string>::iterator it =
            std::find(_listTab.begin(), _listTab.end(), Qstr.toStdString());
    if(it != _listTab.end()) {
        _listTab.erase(it);
    } else {
        WizardLogger::warning("Impossible de trouver l'onglet à l'index: " +
                              std::to_string(i));
    }
    _tab->removeTab(i);
}

void ChatManagerGUI::newTab(QString pseudo){
    std::string strPseudo = pseudo.toStdString();

    std::vector<std::string>::iterator it =
            std::find(_listTab.begin(), _listTab.end(), strPseudo);
    if(strPseudo != Player::getPlayer()->getName() && it == _listTab.end()) {
        ChatWidget* chatWidget = new ChatWidget(strPseudo, this);
        _tab->addTab(chatWidget, pseudo);
        _listTab.push_back(strPseudo);

        connect(this, SIGNAL(sigNewMessage(QString, QString, QString)),
                chatWidget, SLOT(showNewMessage(QString, QString, QString)));
    }

    mtx.unlock();
}

void ChatManagerGUI::newTab(QListWidgetItem* item){
    newTab(item->text());
}
