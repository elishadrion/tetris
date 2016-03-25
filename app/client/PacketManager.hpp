#include <string>
#include <vector>

#include "common/Constants.hpp"
#include "common/Packet.hpp"
#include "common/WizardLogger.hpp"
#include "Connection.hpp"
#include "Card.hpp"
#include "WizardDisplay.hpp"
#include "CacheManager.hpp"
#include "Player.hpp"
#include "GameManager.hpp"

extern WizardDisplay *wizardDisplay;

namespace PacketManager {
    void managePacket(Packet::packet*);

    //=============================RECEV=====================================
    
    /* Login process */
    void loginResult(const Packet::intPacket*); /* LOGIN_RES_ID */
    void playerInfo(const Packet::playerInfoPacket*); /* PLAYER_INFO_ID */
    void loginComplete(const Packet::packet*); /* LOGIN_COMPLETE_ID */
    
    /* Card process */
    void saveCardInfo(const Packet::cardInfosPacket*); /* CARTE_INFO_ID */
    void saveCardImg(const Packet::cardImgPacket*); /* CARTE_IMG_ID */
    
    /* Tchat process */
    void getMessage(const Packet::tchatRecevMsgPacket*); /* TCHAT_RECEV_MSG_ID */
    
    /* Friends process */
    void removeFriend(const Packet::pseudoPacket*); /* FRIEND_DEL_ID */
    void requestFriend(const Packet::pseudoPacket*); /* FRIENDS_REQ_ID */
    void updateFriendList(const Packet::friendListPacket*); /* FRIENDS_LIST_ID */
    
    // Classement
    void manageClassement(Packet::classementPacket*);

    /* Wainting process */
    void askDeckAndPseudo(const Packet::pseudoPacket*); /* GAME_START_ID */
    
    /* Game process */
    void setTurn(const Packet::turnPacket*); /* TURN_ID */
    void setBeginDraw(const Packet::beginDrawPacket*);
    void setDraw(const Packet::intPacket*); /* DRAW_ID */
    void* threadDraw(void*);
    void askDrop(const Packet::intPacket*); /* ASK_DROP_ID */
    void manageAttack(Packet::attackPacket*);
    void managePlaceSpell(Packet::placeAttackSpellPacket*);
    void managePlaceCard(Packet::placeCardPacket*);
    void managePlaceCardAttack(Packet::placeAttackPacket*);
    void manageEndGame(const Packet::endGamePacket*); /* END_GAME_ID */
    
    // Error
    void manageError(Packet::intPacket*);

    //============================SEND======================================
    
    /* Login process */
    void makeLoginRequest(const char*, const char*); /* LOGIN_REQ_ID */
    void makeRegistrationRequest(const char*, const char*); /* REGIST_REQ_ID */
    void sendDisconnection(); /* DISCONNECT_ID */
    
    /* Card process */
    void makeCardImgRequest(const unsigned); /* CARTE_IMG_REQ_ID */
    
    /* Tchat process */
    void sendMessage(const std::string, const std::string); /* TCHAT_SEND_MSG_ID (out) */
    
    /* Friends process */
    void makeFriendRequest(const char*); /* FRIEND_ADD_ID | FRIEND_DEL_ID */
    void makeFriendListRequest(); /* FRIENDS_LIST_REQ_ID */
    
    // Classement
    void askClassement();

    /* Wainting process */
    void makeGameRequest(); /* WAITING_ID */
    void makeGameCancelRequest(); /* CANCEL_ID */
    void sendSelectedDeck(const char[MAX_DECK_NAME]); /* DECK_CHOOS_ID */
    
    /* Game process */
    void sendDrop(const int); /* DROP_ID */
    void sendAttack(const unsigned, const int); // C_ATTACK_ID
    void sendPlaceCard(const unsigned); // C_PLACE_CARD_ID
    void sendPlaceCardAttack(const unsigned, const int); // C_PLACE_CARD_MAKE_SPELL_ID
    void endTurn(); /* END_TURN_ID */
    void quit(); /* QUIT_ID */

}
