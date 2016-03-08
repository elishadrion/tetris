#ifndef LOGINPANEL_GUI_HPP
#define LOGINPANEL_GUI_HPP

#include "GUIDefine.hpp" /* MUST BE FIRST */

#include <string>

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>

#include "PacketManager.hpp"


class LoginPanelGUI : public QWidget {
    Q_OBJECT

    QLabel *pseudo;
    QLabel *mdp;
    QLabel *title;
    QLabel *beginSpace;
    QLabel *endSpace;
    QGridLayout *gridlayout;
    QLineEdit *m_pseudo;
    QLineEdit *m_mdp;
    QHBoxLayout *layout;
    QPushButton *login;
    QPushButton *signIn;
public:
    LoginPanelGUI();
    void printLoginResult(std::string);

public slots:
    void loginDisplayResult(QString);
    void makeLogin();

signals:
    void mustPrintResult(QString);

public:
    ~LoginPanelGUI();

};

#endif LOGINPANEL_GUI_HPP
