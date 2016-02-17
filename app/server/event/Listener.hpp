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
    Listener(); // Saves the new listener in the listListener

    virtual void onGameStart(Game game);
    virtual void onPlayerPlay(Game game, Player player);
    virtual void onPlaceCard(Card card);


    ///// STATIQUE /////
    static void onGameStart(Game game);
    static void onPlayerPlay(Game game, Player player);

    static void onPlaceCard(Card card);



    /*
     * When a static function is called, we call this function for all Listeners.
     * The function that (?) would like a Listener action must to inherit this class
     * and override the good function
     * I think we can use an Object in place of a function
     */


};



#endif	/* LISTENER_HPP */

