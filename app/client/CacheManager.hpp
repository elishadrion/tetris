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
public:
    CacheManager() = default;
    ~CacheManager();
    
    static Card *getCard(unsigned);
    static Card *getCard(std::string);
    
    static void addCard(Card*);
    static unsigned getNbrCard();
};

#endif  /* CACHE_MANAGER_HPP */
