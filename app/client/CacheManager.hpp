#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

#include <string>
#include <vector>

#include "Card.hpp"
#include "PacketManager.hpp"

#include "common/WizardLogger.hpp"

class CacheManager {
    std::vector<Card*> cardCache;
    bool waiting;
    
    Card *requestCard(unsigned);
public:
    CacheManager() = default;
    ~CacheManager();
    
    Card *getCard(unsigned);
    Card *getCard(std::string);
    
    void addToCache(Card*);
};

#endif  /* CACHE_MANAGER_HPP */
