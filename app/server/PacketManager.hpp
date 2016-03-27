#include <string>

#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "common/Error.hpp"

#include "Card.hpp"
#include "Collection.hpp"
#include "PlayerManager.hpp"

class Player;
class PlayerInGame;
class Game;

namespace PacketManager {
    void managePacket(Player*, Packet::packet*);
    
    //=============================RECEV=====================================
    
    /* Login process */
    void manageDisconnectRequest(Player*, Packet::packet*); /* DISCONNECT_ID */
    
    /* Card process */
    void manageCardImgRequest(Player*, Packet::intPacket*); /* CARTE_IMG_REQ_ID */
    
    /* Tchat process */
    void playerSendMsg(Player*, const Packet::tchatSendMsgPacket*); /* TCHAT_SEND_MSG_ID */
    
    /* Friend process */
    void manageFriendRequest(Player*, Packet::pseudoPacket*); /* FRIEND_ADD_ID | FRIEND_DEL_ID */
    void manageFriendListRequest(Player*, Packet::packet*); /* FRIENDS_LIST_REQ_ID */
    
    /* Launching game process */
    void managNewGameRequest(Player*, Packet::packet*); /* WAITING_ID */
    void managCancelGameRequest(Player*, Packet::packet*); /* CANCEL_ID */
    void manageChooseDeck(Player*, Packet::deckPacket*); /* DECK_CHOOS_ID */
    
    /* Game process */
    void manageDrop(Player*, Packet::intPacket*); /* DROP_ID */
    void manageAttack(Player*, Packet::twoCardPacket*); /* C_ATTACK_ID */
    void managePlaceCard(Player*, Packet::intPacket*); // C_PLACE_CARD_ID
    void managePlaceAttackCard(Player*, Packet::twoCardPacket*); // C_PLACE_CARD_MAKE_SPELL_ID
    void manageEndTurn(Player*, Packet::packet*); /* END_TURN_ID */
    void manageQuitGame(Player*, Packet::packet*); /* QUIT_ID */

    /* Classement */
    void sendClassement(Player*, std::vector<std::string>,std::vector<int>, std::vector<int>); /* SEND_CLASSEMENT_ID */
    
    //===========================SEND==========================================
    
    /* Card process */
    void sendCardInfo(Player*, Card*); /* CARTE_INFO_ID */
    void sendCardImg(Player*, Card*); /* CARTE_IMG_ID */
    void sendDeck(Player*);
    
    /* Tchat process */
    void sendPlayerRecdvMsg(Player*, std::string, std::string, std::string); /* TCHAT_RECEV_MSG_ID */
    
    /* Friend process */
    void sendFriendRequest(Player*, std::string); /* FRIENDS_REQ_ID */
    void sendFriendList(Player*); /* FRIENDS_LIST_ID */
    
    /* Game process */
    void askDeck(Player*, std::string); /* ASK_DECK_AND_PSEUDO_ID */
    void sendTurnInfo(Player*, unsigned, bool); /* TURN_ID */
    void sendCard(Player*, Card*); /* DRAW_ID (nullptr for other player sync) */
    void sendDrawBegin(Player*, std::vector<unsigned>);
    void sendAdverseDraw(Player*); /* ADVERSE_DRAW_ID */
    void askDefausse(Player*, int); /* ASK_DROP_ID */
    void sendDrop(Player*, int); /* DROP_ID (for second player sync, amount of drop) */
    void sendAttack(Player*, std::string, int, unsigned, int, unsigned);
    void sendPlaceMonsterCard(Player*, std::string, int, int);
    void sendPlaceMonsterCard(Player*, std::string, int, int, int, unsigned, unsigned);
    void sendPlaceSpellCard(Player*, std::string, int, int, unsigned, unsigned);
    void playerDamage(Player*, std::string, int); /* PLAYER_DAMAGE_ID */
    void sendEndGame(Player*, int, int); /* END_GAME_ID (-1: lose | 0: null | 1:win + new card) */


    void sendError(Player*, Error);

}
