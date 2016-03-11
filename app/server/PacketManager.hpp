#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"

#include "Card.hpp"
#include "Collection.hpp"

class Player;
class PlayerInGame;
class Game;

namespace PacketManager {
    void managePacket(Player*, Packet::packet*);
    
    //=============================RECEV=====================================
    
    /* Login process */
    void manageDisconnectRequest(Player*, Packet::packet*); /* DISCONNECT_ID */
    
    /* Card process */
    void manageCardRequest(Player*, Packet::intPacket*); /* CARTE_REQ_ID */
    void manageCardImgRequest(Player*, Packet::intPacket*); /* CARTE_IMG_REQ_ID */
    
    /* Tchat process */
    void manageConvRequest(Player*, Packet::pseudoPacket*); /* TCHAT_CONV_REQ_ID */
    void manageMessageTchat(Player*, Packet::tchatMessagePacket*); /* TCHAT_MESSAGE_ID (in) */
    void manageConvQuitRequest(Player*, Packet::pseudoPacket*); /* TCHAT_END_REQ_ID */
    
    /* Friend process */
    void manageFriendRequest(Player*, Packet::pseudoPacket*); /* FRIEND_ADD_ID | FRIEND_DEL_ID */
    void manageFriendListRequest(Player*, Packet::packet*); /* FRIENDS_LIST_REQ_ID */
    
    /* Launching game process */
    void managNewGameRequest(Player*, Packet::packet*); /* WAITING_ID */
    void managCancelGameRequest(Player*, Packet::packet*); /* CANCEL_ID */
    void manageChooseDeck(Player*, Packet::intPacket*); /* DECK_CHOOS_ID */
    
    /* Game process */
    void manageDrop(Player*, Packet::intPacket*); /* DROP_ID */
    void manageAttack(Player*, Packet::attackPacket*); /* ATTACK_ID (in) */
    void manageSpell(Player*, Packet::attackPacket*); /* SPELL_ID (in) */
    void manageEndTurn(Player*, Packet::packet*); /* END_TURN_ID */
    void manageQuitGame(Player*, Packet::packet*); /* QUIT_ID */
    
    //===========================SEND==========================================
    
    /* Card process */
    void sendCardInfo(Player*, Card*); /* CARTE_INFO_ID */
    void sendCardImg(Player*, Card*); /* CARTE_IMG_ID */
    
    /* Tchat process */
    void startConv(Player*, std::string); /* TCHAT_NEW_CONV_ID */
    void sendMessageTchat(Player*, std::string); /* TCHAT_MESSAGE_ID (out) */
    void endConv(Player*, std::string); /* TCHAT_END_CONV_ID */
    
    /* Friend process */
    void sendFriendRequest(Player*, std::string); /* FRIENDS_REQ_ID */
    void sendFriendList(Player*); /* FRIENDS_LIST_ID */
    
    /* Game process */
    void initGame(Player*, std::string); /* LAUNCH_ID */
    void sendTurnInfo(Player*, std::string, PlayerInGame*, PlayerInGame*); /* TURN_ID (force sync) */
    void sendCard(Player*, Card*); /* DRAW_ID (nullptr for other player sync) */
    void askDefausse(Player*, int); /* ASK_DROP_ID */
    void sendDrop(Player*, int); /* DROP_ID (for second player sync, amount of drop) */
    void sendAttack(Player*, std::string, int, int, unsigned int); /* ATTACK_ID (out) */
    void sendSpell(Player*, std::string, int, int, unsigned int); /* SPELL_ID (out) */
    void sendEndGame(Player*, int, int); /* END_GAME_ID (-1: lose | 0: null | 1:win + new card) */
}
