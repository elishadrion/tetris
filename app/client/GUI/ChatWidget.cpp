#include "ChatWidget.hpp"


ChatWidget::ChatWidget(std::string pseudo, QWidget* parent): _friend(pseudo),QWidget(parent){

    _gridlayout = new QGridLayout(this);

    _layout = new QHBoxLayout();

    _text=new QTextBrowser(this);

    _send = new QPushButton("Envoyer");
    _m_send= new QLineEdit(this);

    _layout->addWidget(_m_send);
    _layout->addWidget(_send);

    _gridlayout->addWidget(_text,0,0);
    _gridlayout->addLayout(_layout,1,0);

    QObject::connect(_send,SIGNAL(clicked()),this,SLOT(sendMessage()));
}

void ChatWidget::sendMessage(){
    PacketManager::sendMessage(_friend, _m_send->text().toStdString());
    _m_send->clear();
}

void ChatWidget::showNewMessage(QString playerFrom, QString playerTo,
                                QString msg) {
    if(_friend == playerFrom.toStdString() || _friend == playerTo.toStdString()) {
        QString text = playerFrom;
        text += " -> ";
        text += playerTo;
        text += ": ";
        text += msg;
        _text->append(text);
    }
}
