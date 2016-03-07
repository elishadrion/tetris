#ifndef LOGINPANEL_GUI_HPP
#define LOGINPANEL_GUI_HPP

/* Remove ncurses definition */
#ifdef scroll
#undef scroll
#endif
#ifdef border
#undef border
#endif

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class LoginPanelGUI : public QWidget {
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
};

#endif LOGINPANEL_GUI_HPP
