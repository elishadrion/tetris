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

#include "client/WizardDisplay.hpp"
extern WizardDisplay *wizardDisplay;


class GUI;
class LoginPanelGUI;
#include "GUI.hpp"
#include "MenuPanelGUI.hpp"


class LoginPanelGUI : public QWidget {
    Q_OBJECT

    GUI* _gui;

    QLabel *_pseudo;
    QLabel *_mdp;
    QLabel *_title;
    QGridLayout *_gridlayout;
    QLineEdit *_m_pseudo;
    QLineEdit *_m_mdp;
    QHBoxLayout *_layout;
    QPushButton *_login;
    QPushButton *_signIn;

    std::string _strPseudo;
    std::string _strMdp;

    void login(bool);
    void loginDisplayResult(std::string);
    void displayMainMenu();

public:
    LoginPanelGUI(GUI*);

public slots:
    void makeLogin();
    void makeRegister();
    void setStrPseudo(QString);
    void setStrMdp(QString);


};

#endif // LOGINPANEL_GUI_HPP
