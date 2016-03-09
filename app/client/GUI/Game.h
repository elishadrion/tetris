#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QTabWidget>
#include <QTabBar>
#include <QGroupBox>


class Game : public QWidget {
public:
    Game();
private:
//    QLabel *pseudo;
//    QLabel *mdp;
//    QLabel *title;
//    QLabel *beginSpace;
//    QLabel *endSpace;
    QGridLayout *gridlayout;
//    QLineEdit *m_pseudo;
//    QLineEdit *m_mdp;
//    QHBoxLayout *layout;
//    QPushButton *login;
//    QPushButton *signIn;
};

#endif // GAME_H
