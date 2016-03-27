
#include "PubManager.hpp"

std::vector<PubManager*> PubManager::_allPub;

PubManager::PubManager(std::string nom, QWidget* parent):
    QWidget(parent) {

    _label = new QLabel(this);
    _label->setScaledContents(true);
    _label->setFixedSize(0,0);
    std::string image = ":/Images/Pub/" ;
    image += nom;
    image += ".png";
    QPixmap pic(QString(image.c_str()));
    _label->setPixmap(pic);
}

/**
 * Call when the widget is resize
 *
 * @param event
 */
void PubManager::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);
    QSize picSize = _label->pixmap()->size();
    picSize.scale(size(),Qt::KeepAspectRatioByExpanding);
    _label->setFixedSize(picSize);
}

void PubManager::initAllPub() {
    _allPub.push_back(new PubManager("chronophone"));
    _allPub.push_back(new PubManager("niouzz"));
    _allPub.push_back(new PubManager("tfou"));
}

PubManager* PubManager::getRandomPub() {
    srand(time(NULL));
    int choosePub = rand() % static_cast<int>(_allPub.size()); // Chose random
    return _allPub[choosePub];
}
