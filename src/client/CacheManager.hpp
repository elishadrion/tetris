#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

class CacheManager;

#include <string>
#include <vector>

#include "PacketManager.hpp"
#include "../common/WizardLogger.hpp"

extern WizardDisplay *display;

class CacheManager {
    static std::vector<std::string*> pseudoRankingCache;
    static std::vector<int> victoryRankingCache;
    static std::vector<int> defeatRankingCache;
public:
    CacheManager() = default;
    ~CacheManager();
    
    static int getRankingSize();
    static std::string *getPseudoRanking(int);
    static int getVictoryRanking(int);
    static int getDefeatRanking(int);
    
    static void addPseudoRanking(std::string*);
    static void addVictoryRanking(int);
    static void addDefeatRanking(int);
    
    static void clearRankingCache();
};

#endif  /* CACHE_MANAGER_HPP */
