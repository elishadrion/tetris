#include "CacheManager.hpp"

CacheManager::~CacheManager() {
    /* Delete all card in cache */
    for (int i = 0 ; i < cardCache.size() ; ++i) {
        delete cardCache[i];
    }
    
    /* Erase all vector */
    cardCache.clear();
}

/* Get card by ID from card local cache
 * @param ID : the ID of the card to find
 * @return the card pointer or nullptr if card's ID don't exist
 */
Card *CacheManager::getCard(unsigned ID) {
    Card *card;
    /* Search for card ID in cache */
    for (int i = 0 ; i < cardCache.size() ; ++i) {
        card = cardCache[i];
        if (card->getID() == ID)
            return card;
    }
    
    /* Card not found so we must add it to cache */
    WizardLogger::warning("La carte "+std::to_string(ID)+" n'est pas dans le cache, requête auprès du serveur");
    card = requestCard(ID);
    
    /* Search for card ID in cache */
    for (int i = 0 ; i < cardCache.size() ; ++i) {
        card = cardCache[i];
        if (card->getID() == ID)
            return card;
    }
    
    WizardLogger::error("La carte demandé semble ne pas exister ! Veuillez vérifier son ID");
    
    return nullptr;
}

/* Get card by name from card local cache
 * @param name : the name of the card to find
 * @return the card pointer or nullptr if card isn't found in cache (error)
 */
Card *CacheManager::getCard(std::string name) {
    /* Search for card ID in cache */
    for (int i = 0 ; i < cardCache.size() ; ++i) {
        if (cardCache[i]->getName() == name)
            return cardCache[i];
    }
    
    /* Card not found so we must add it to cache */
    WizardLogger::error("La carte "+name+" n'est pas dans le cache (cache incomplet ?)");
    
    return nullptr;
}

/* Add card to cache and stop waiting for it */
void CacheManager::addToCache(Card* card) {
    if (card != nullptr)
        cardCache.push_back(card);
    waiting = false;
}

//=========================PRIVATE========================

Card *CacheManager::requestCard(unsigned ID) {
    waiting = true;
    PacketManager::makeCardRequest(ID);
    while(waiting);
}
