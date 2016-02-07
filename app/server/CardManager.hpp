/*
 * File:   CardManager.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 15:00
 */

#ifndef CARDMANAGER_HPP
#define	CARDMANAGER_HPP

#include <map>


#include "Effect.hpp"
#include "../common/Card.hpp"

/**
 * Load and save Card on file
 * (Must not be a Class #JavaPower)
 */
class CardManager {

    static std::map<int, Card&> listCard; // List of card (with id and card)


public:
    static void loadCards();
    virtual Card& loadCard(std::size_t id);


    virtual ~CardManager() = default;
};




#endif	/* CARDMANAGER_HPP */

