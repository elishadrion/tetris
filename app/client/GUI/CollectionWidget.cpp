#include "CollectionWidget.hpp"

CollectionWidget::CollectionWidget(): QWidget(){
    page=0;
    currentPage=1;

    _grid = new QGridLayout(this);

    _grid->setColumnStretch(0,2);
    _grid->setColumnStretch(1,2);
    _grid->setColumnStretch(2,2);
    _grid->setColumnStretch(3,2);
    _grid->setColumnStretch(4,2);

    _pages = new QTabWidget();
    _pages->tabBar()->hide();
    _grid->addWidget(_pages,0,0,1,5);

    _pageLabel = new QLabel();
    _pageLabel->setText(QString::fromStdString(std::to_string(page+1)));
    _pageLabel->setAlignment(Qt::AlignCenter);
    _grid->addWidget(_pageLabel,1,2);

    _next = new QPushButton("Suivant");
    _previous = new QPushButton("Précédent");
    _grid->addWidget(_previous,1,0);
    _grid->addWidget(_next,1,4);

    std::size_t taille = 0;
    _collection = Player::getPlayer()->getCollection();
    if(_collection != nullptr && sizeof(_collection[0]) != 0) {
        taille = sizeof(_collection)/sizeof(_collection[0]);
    }

    tempPage = new PageWidget();
    for(std::size_t i = 0; i < taille; i++){
    	if(i%10 == 0){
    		page+=1;
            tempPage = new PageWidget();
            _pages->addTab(tempPage,QString::fromStdString(std::to_string(page)));
    	}
    	CardWidget *card= new CardWidget(CacheManager::getCard(_collection[i]));
    	tempPage->addCard(card);
    }

    connect(_next,SIGNAL(clicked()),this,SLOT(nextPage()));
    connect(_previous,SIGNAL(clicked()),this,SLOT(previousPage()));
}

void CollectionWidget::nextPage(){
    if (_pages->currentIndex() < _pages->count()-1){
        _pages->setCurrentIndex(_pages->currentIndex()+1);
        currentPage+=1;
        _pageLabel->setText(QString::fromStdString(std::to_string(currentPage)));
    }
}

void CollectionWidget::previousPage(){
    if (_pages->currentIndex() > 0){
        _pages->setCurrentIndex(_pages->currentIndex()-1);
        currentPage-=1;
        _pageLabel->setText(QString::fromStdString(std::to_string(currentPage)));
    }
}
