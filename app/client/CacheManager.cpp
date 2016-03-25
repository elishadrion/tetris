#include "CacheManager.hpp"

std::vector<Card*> CacheManager::cardCache;
std::vector<std::string*> CacheManager::pseudoRankingCache;
std::vector<int> CacheManager::victoryRankingCache;
std::vector<int> CacheManager::defeatRankingCache;

CacheManager::~CacheManager() {
    /* Delete all card in cache */
    for (int i = 0 ; i < cardCache.size() ; ++i) {
        delete cardCache[i];
    }
    
    /* Erase all vector */
    cardCache.clear();
    
    clearRankingCache();
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
    
    WizardLogger::error("La carte demandé semble ne pas exister ! Veuillez vérifier son ID");
    
    return nullptr;
}

int CacheManager::getRankingSize() { return pseudoRankingCache.size(); } 
std::string *CacheManager::getPseudoRanking(int i) { return pseudoRankingCache[i]; }
int CacheManager::getVictoryRanking(int i) { return victoryRankingCache[i]; }
int CacheManager::getDefeatRanking(int i) { return defeatRankingCache[i]; }

/* Safe new card in cache (thread safe) */ 
void CacheManager::addCard(Card* newCard) {
    if (newCard != nullptr)
        cardCache.push_back(newCard);
}

void CacheManager::addPseudoRanking(std::string *pseudo) {
    pseudoRankingCache.push_back(pseudo);
}

void CacheManager::addVictoryRanking(int victory) {
    victoryRankingCache.push_back(victory);
}

void CacheManager::addDefeatRanking(int defeat) {
    defeatRankingCache.push_back(defeat);
}

unsigned CacheManager::getNbrCard() {
    return static_cast<unsigned>(cardCache.size());
}

void CacheManager::clearRankingCache() {
    /* Delete all pseudo in cache */
    for (int i = 0 ; i < pseudoRankingCache.size() ; ++i) {
        delete pseudoRankingCache[i];
    }
    
    /* Erase all vector */
    pseudoRankingCache.clear();
    victoryRankingCache.clear();
    defeatRankingCache.clear();
}
