#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

#include <string>
#include <vector>

#include "Card.hpp"
#include "PacketManager.hpp"

#include "common/WizardLogger.hpp"

class CacheManager {
    static std::vector<Card*> cardCache;
    static bool waiting;
    
    static Card *requestCard(unsigned);
public:
    CacheManager() = default;
    ~CacheManager();
    
    static Card *getCard(unsigned);
    static Card *getCard(std::string);
    
    void addToCache(Card*);
};

#endif  /* CACHE_MANAGER_HPP */
