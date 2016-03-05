#ifndef LOGINPANEL_HPP
#define LOGINPANEL_HPP

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class LoginPanel : public QWidget
{
public:
    LoginPanel();
private:
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

};

#endif // LOGINPANEL_HPP
