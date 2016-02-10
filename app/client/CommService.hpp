#ifndef COMMSERVICE_HPP
#define	COMMSERVICE_HPP

#include <string>
#include <list>

#include "common/Packet.hpp"

using namespace std;

class CommService {
    
    void manageCollectionListPacket(Packet::collectionListPacket*);
public:
    /* API for other service */
    void managePacket(Packet::packet*);
    void makeLoginRequest(const string, const string);
    void sendDisconnection();
    void requestCollection();
};

#endif	/* COMMSERVICE_HPP */
