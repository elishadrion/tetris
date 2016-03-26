#ifndef ERROR_HPP
#define	ERROR_HPP

#include <string>

enum Error {
    NoError = 0,
    NotEnoughEnergy = 1,
    NotEnoughPlace = 2,
    NotHisTurn = 3,
    MustAttackTaunt = 4,
    UnknowError = 5,
    NotEffectForPlayer = 6,
    NotEffectForMonster = 7,
    MaxCardInDeck = 8, /* The number of card in deck is limited */
    SameCardMax = 9, /* The number of the same card in a collection/deck */
    CollectionFull = 10, /* The number of card in collection is limited */
    MaxDeck = 11, /* The number of deck is limited */
    MustOneDeckMin = 12, /* The player must have one deck */
    DeckNotFound = 13,
    CardNotFound = 14,
    NotFirstTurn = 15
};

namespace ErrorAPI {
    std::string errorToStr(int);
}


#endif	/* ERROR_HPP */
