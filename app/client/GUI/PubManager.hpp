#ifndef PUBMANAGER_GUI_HPP
#define PUBMANAGER_GUI_HPP

#include <vector>

#include <QWidget>
#include <QLabel>


class PubManager : public QWidget {

    QLabel* _label;
    std::string _nom;

    static std::vector<PubManager*> _allPub;
    PubManager(std::string nom, QWidget* = 0);

public:
    static PubManager* getRandomPub();
    static void initAllPub();
    void resizeEvent(QResizeEvent*);

};




#endif // PUBMANAGER_GUI_HPP
