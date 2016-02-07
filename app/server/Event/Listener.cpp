
#include "Listener.hpp"

void Listener::onPlaceCard(Card card) {
    for(vector<Listener>::iterator itListener = listListener.begin(); i != listListener.end();++i){
        itListener->onPlaceCard(card);
    }
}

/**
 * Constructor
 */
Listener::Listener() {
    listListener.push_back(this);
}
