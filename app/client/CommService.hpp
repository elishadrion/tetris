#ifndef COMMSERVICE_HPP
#define	COMMSERVICE_HPP

#include <string>
#include <list>

#include "common/Packet.hpp"

using namespace std;

class CommService {
    
    void manageCollectionListPacket(collectionListPacket*);
public:
    /* API for other service */
    void managePacket(void*);
    void makeLoginRequest(const String, const String);
    void sendDisconnection();
    void requestCollection();
};

#endif	/* COMMSERVICE_HPP */
