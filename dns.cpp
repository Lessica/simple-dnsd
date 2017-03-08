/*!
*****************************************************************************
*  \file dns.cpp
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

#include "dns.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <sstream>

using namespace std;

/*! Constructor
 */
CDns::CDns(char *outFile)
        : m_Socket(0),
          m_Error(false),
          m_ClientAddr(),
          m_DnsDb(),
          m_Log(outFile) {
}

/*! Destructor
 */
CDns::~CDns() {
}

/*! Starts communication with the resolver
*/
void CDns::openCommunication() {
    struct sockaddr_in server;
    int length;

    // creates a socket
    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (m_Socket < 0) {
        cerr << "Error opening socket" << endl;
        exit(0);
    }

    // binds it to listen to the DNS_PORT
    length = sizeof(server);
    memset(&server, 0, (size_t) length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(DNS_PORT);

    if (::bind(m_Socket, (struct sockaddr *) &server, length) < 0) {
        cerr << "Error binding socket" << endl;
        exit(0);
    }

    // Prepare Dns db class to process file
    bool error = m_DnsDb.readConfigFile("ip_hosts");
    if (error) {
        cerr << "Error reading <ip_hosts> config file. It does not exist" << endl;
        exit(0);
    }
    m_Log.printString("Starting name server...");
}

/*! Reads message from client
 */
void CDns::readMessage() {
    socklen_t fromlen = sizeof(struct sockaddr_in);
    ssize_t n;
    char buffer[1024];

    // receives a new message
    n = recvfrom(m_Socket, (void *) buffer, 1024, 0, (struct sockaddr *) &m_ClientAddr, &fromlen);
    if (n < 0) {
        cerr << "Error receiving from " << m_Socket << " socket" << endl;
        exit(0);
    }
    // Conversion of the buffer received from char* to string
    string message_received((const char *) &buffer, (unsigned long) n);
    // The original message will be passed as parameter to the different
    // methods inside the clas to be reused on the response transmission
    // Call to ParseMessage
    parseMessage(message_received, (unsigned long) n);
}

/*! Sends message to client
 */
void CDns::sendMessage(string &txMessage) {
    ssize_t n;
    socklen_t tolen = sizeof(struct sockaddr_in);

    m_Log.printString("\nMessage (sent):");
    m_Log.printFormattedString(txMessage);

    // sends message back to resolver
    n = sendto(m_Socket, txMessage.c_str(), txMessage.size(),
               0, (struct sockaddr *) &m_ClientAddr, tolen);
    if (n < 0) {
        cerr << "Error sending to " << m_Socket << " socket" << endl;
        exit(0);
    }
}

/*! Parses the message received
 */
void CDns::parseMessage(string &txMessage, unsigned long inLength) {
    // A new message is created
    m_Message = new CMessage(m_Log);

    // Initialize error variable
    m_Error = false;

    // Conversion of string to be logged in a file
    ostringstream s;
    s << DNS_PORT;
    m_Log.printString("\n----- Message received from socket (port " + s.str() + ") -----");
    m_Log.printString("--------------------------------------------------");

    m_Log.printString("\nMessage (received):");
    m_Log.printFormattedString(txMessage);

    // Header: 12 bytes (RFC 1035)
    string header(txMessage, 0, HEADER_SIZE);
    m_Error = m_Message->setHeader(header);
    if (m_Error) {
        m_Log.printString("parseMessage: error parsing header");
        // Let's build the response
        buildMessage(txMessage);
        return;
    }

    // Question: variable length. We assume there is only
    // 1 question section. If there are more, a not implemented
    // has been already returned.
    string question(txMessage, HEADER_SIZE, inLength - HEADER_SIZE);
    m_Error = m_Message->setQuestion(question, inLength - HEADER_SIZE);
    if (m_Error) {
        m_Log.printString("parseMessage: error parsing question");
        // Let's build the response
        buildMessage(txMessage);
        return;
    }
    // No errors, let's look for the host
    hostLookup(txMessage);
}


/*! Looks for the host in the Db
 */
void CDns::hostLookup(string &txMessage) {
    struct in_addr addr;
    unsigned long saddr;
    string hostname;

    // Get hostname from message class
    hostname = m_Message->getHost();

    // Look for the IP address inside Db
    addr.s_addr = m_DnsDb.getAddress(hostname.c_str());
    // Get the address in network order
    saddr = htonl(addr.s_addr);

    ostringstream s;
    s << hostname.size();
    m_Log.printString("Host " + hostname + " (" + s.str() + ")");

    // Let's update the address for the reply
    m_Error = m_Message->setAnswer(saddr);
    if (m_Error) {
        m_Log.printString("hostLookup: address not found");
    }
    // Build the message to send it back
    buildMessage(txMessage);
}

/*! Build message with the response
 */
void CDns::buildMessage(string &txMessage) {
    // txMessage has already the original data to be reused.
    // To reply faster, only the header will be stored,
    // all question section will the same one.

    m_Message->getHeader(txMessage);

    if (!m_Error) {
        // appends Answer, Authority and Additional
        // in case they exist.
        txMessage += m_Message->getAnswer();
        txMessage += m_Message->getAuthority();
        txMessage += m_Message->getAdditional();
    }

    // Now txMessage contains all the information
    // to be sent back to the resolver.
    sendMessage(txMessage);
}
