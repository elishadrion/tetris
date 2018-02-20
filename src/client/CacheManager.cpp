#include "CacheManager.hpp"


std::vector<std::string*> CacheManager::pseudoRankingCache;
std::vector<int> CacheManager::victoryRankingCache;
std::vector<int> CacheManager::defeatRankingCache;

CacheManager::~CacheManager() {
    
    clearRankingCache();
}


int CacheManager::getRankingSize() { return pseudoRankingCache.size(); } 
std::string *CacheManager::getPseudoRanking(int i) { return pseudoRankingCache[i]; }
int CacheManager::getVictoryRanking(int i) { return victoryRankingCache[i]; }
int CacheManager::getDefeatRanking(int i) { return defeatRankingCache[i]; }


void CacheManager::addPseudoRanking(std::string *pseudo) {
    if(pseudo->size() > 0) {
        pseudoRankingCache.push_back(pseudo);
    }
}

void CacheManager::addVictoryRanking(int victory) {
    victoryRankingCache.push_back(victory);
}

void CacheManager::addDefeatRanking(int defeat) {
    defeatRankingCache.push_back(defeat);
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
