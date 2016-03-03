#ifndef CACHE_MANAGER_HPP
#define CACHE_MANAGER_HPP

#include <string>
#include <vector>

#include "Card.hpp"

#include "common/WizardLogger.hpp"

class CacheManager {
    std::vector<Card*> cardCache;
    
    Card *addToCache(unsigned);
public:
    CacheManager() = default;
    ~CacheManager();
    
    Card *getCard(unsigned);
    Card *getCard(std::string);
};

#endif  /* CACHE_MANAGER_HPP */
