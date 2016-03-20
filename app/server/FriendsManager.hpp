#ifndef FRIENDSMANAGER_HPP
#define	FRIENDSMANAGER_HPP

#include <string>

#include "PlayerManager.hpp"

namespace FriendsManager {
    /* Save friend request for a specific player (from a player) */
    void saveFriendRequest(Player*, Player*);
    /* Save new friends */
    void acceptFriendRequest(Player*, Player*);
    /* Reject friend request and notify waiting player */
    void rejectFriendRequest(Player*, Player*);
    /* Cancel friendship */
    void cancelFriendship(Player*, Player*);
};

#endif	/* FRIENDSMANAGER_HPP */
