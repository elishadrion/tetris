#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QApplication>
#include <QWidget>
#include <string>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QTextBrowser>

class ChatWidget : public QWidget{
Q_OBJECT
public:
    ChatWidget(std::string pseudo);

private:
    std::string _friend;
    QHBoxLayout *_layout;
    QGridLayout *_gridlayout;
    QPushButton *_send;
    QTextBrowser *_text;
    QLineEdit *_m_send;

private slots:
    void sendMessage();
};

#endif // CHATWIDGET_H
