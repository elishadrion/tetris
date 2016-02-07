/*
 * File:   Listener.hpp
 * Author: Detobel36
 *
 * Created on 3 février 2016, 9:28
 */

#ifndef LISTENER_HPP
#define	LISTENER_HPP

class Listener {

    std::vector<Listener> listListener;

public:
    Listener(); // Save the new listener in the listListener

    virtual void onGameStart(Game game);
    virtual void onPlayerPlay(Game game, Player player);
    virtual void onPlaceCard(Card card);


    ///// STATIQUE /////
    static void onGameStart(Game game);
    static void onPlayerPlay(Game game, Player player);

    static void onPlaceCard(Card card);



    /*
     * When a static function is call, we call this function for all Listener.
     * The function the would like a Listener action must to inherit this class
     * and override the good function
     * I think we can use Object in place of function
     */


};



#endif	/* LISTENER_HPP */

