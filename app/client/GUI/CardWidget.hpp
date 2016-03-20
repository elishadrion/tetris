#ifndef CARDWIDGET_HPP
#define CARDWIDGET_HPP

#include <string>
#include <QApplication>
#include <QWidget>
#include <QPalette>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <sstream>

class CardWidget : public QWidget{
    Q_OBJECT

    QString _energy;
    QString _attack;
    QString _life;

    QPainter *_paint;

    QPalette *_palette;
    QPixmap *_pixmap;

public:
    CardWidget(unsigned, unsigned, unsigned);
    void resizeEvent(QResizeEvent*);
    void setAttack(unsigned);
    void setLife(unsigned);
    std::string UnsignedToString(unsigned);
    void actualize();
};

#endif // CARDWIDGET_HPP
