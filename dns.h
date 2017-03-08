/*!
*****************************************************************************
*  \file dns.h
*
*  \brief   Dns server (standard query support only)
*
*  Message handling that includes the reception of a packet, the management
*  of that packet and the transmission of a response packet.
*
*  Right now it is single thread, meaning that it is only possible to 
*  handle one request, process it and reply at a time. In future releases,
*  to have a more eficient name server, a pool of threads will handle
*  a queue of requests.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#ifndef _DNS_H
#define _DNS_H

#include "log.h"
#include "message.h"
#include "dnsDb.h"

#include <netinet/in.h>

/*! \class CDns
 *  \brief It takes care of all related to message handling
 *
 *   CDns receives a message from the client. It gets the new packet and 
 *   parses it. The packet is processed and a response is built. Then
 *   CDns sends the packet back to the client with the right response.
 *
 */
using namespace std;

class CDns {
public:
    /*! Constructor
     */
    CDns(char *outFile);

    /*! Destructor
     */
    ~CDns();

    //
    // Functions taking care of the communications
    //

    /*! Starts communication with the resolver
     */
    void openCommunication();

    /*! Reads message from client
     */
    void readMessage();

    /*! Sends message to client
     */
    void sendMessage(string &txMessage);

    //
    //  Functions taking care of the parsing of the query and
    //  the building of the correct response for the client
    //

    /*! Parses the message received
     */
    void parseMessage(string &txMessage, unsigned long inLength);

    /*! Looks for the host in the Db
     */
    void hostLookup(string &txMessage);

    /*! Build message with the response
     */
    void buildMessage(string &txMessage);

private:
    //  Creation of all data types for the message (RFC 1035)
    //  involving different classes within the process
    static const unsigned short DNS_PORT = 53; /**<  Port used for the DNS. Another solution is to get it from
                                                   the file /etc/services. As this service is very stable,
						   I have discarded that possibility */
    static const unsigned short HEADER_SIZE = 12; /**<  Size of the header of the message. It is a fixed value,
                                                      following RFC 1035 it is 12 bytes */
    int m_Socket;     /**<  Socket to communicate with the client */
    bool m_Error;      /**<  Error */
    CMessage *m_Message;    /**<  CMessage class */
    struct sockaddr_in m_ClientAddr; /**<  Address of the client */
    CDnsDb m_DnsDb;      /**<  CDnsDb class */
    CLog m_Log;        /**<  Log file class */
};

#endif
