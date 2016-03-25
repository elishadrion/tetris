#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

#include <string>
#include <vector>

#include "Card.hpp"
#include "PacketManager.hpp"

#include "common/WizardLogger.hpp"

extern WizardDisplay *wizardDisplay;

class CacheManager {
    static std::vector<Card*> cardCache;
    static std::vector<std::string*> pseudoRankingCache;
    static std::vector<int> victoryRankingCache;
    static std::vector<int> defeatRankingCache;
public:
    CacheManager() = default;
    ~CacheManager();
    
    static Card *getCard(unsigned);
    static int getRankingSize();
    static std::string *getPseudoRanking(int);
    static int getVictoryRanking(int);
    static int getDefeatRanking(int);
    
    static void addCard(Card*);
    static void addPseudoRanking(std::string*);
    static void addVictoryRanking(int);
    static void addDefeatRanking(int);
    
    static unsigned getNbrCard();
};

#endif  /* CACHE_MANAGER_HPP */
