/*!
*****************************************************************************
*  \file header.h
*
*  \brief   Dns header handling
*
*  The header section format is the following one:
*
*      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                      ID                       |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    QDCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    ANCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    NSCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                    ARCOUNT                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*
*  (Ref: RFC 1035). And all the management of these fields is carried here.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#ifndef _HEADER_H
#define _HEADER_H

#include <string>

/*! \class CHeader
 *  \brief It takes care of all related to header section handling
 *
 *  It checks for errors in the different parts of the header that it
 *  will be returned to CMessage. Anyway, it keeps all the information
 *  to send the right one to CMessage when requested
 *
 *
 */
using namespace std;

class CHeader {
public:

    /*! Constructor
     */
    CHeader();

    /*! Destructor
     */
    ~CHeader();

    /*! Error codes (RFC 1035)
     */
    enum TRCode {
        NO_ERROR,
        FORMAT_ERROR,
        SERVER_FAILURE,
        NAME_ERROR,
        NOT_IMPLEMENTED,
        REFUSED
    };

    TRCode setOpCodePart(unsigned char c);

    unsigned char getOpCodePart();

    void setRCode(unsigned char c);

    unsigned char getRCode();

    TRCode setAllCounts(string &buffer);

    string &getAllCounts();

    /*! Used mostly during the error management
     *  Otherwise it will updated to 1 when
     *  sending the response
     */
    void setAnCount(unsigned int anCount);

private:
    /*
    // short should be the type used, but as it takes longer process time than int
    // within 32-bit x86 architectures I will use int type instead
    */
    unsigned char m_OpCodePart;
/**< QR, AA, TC, RD, RA bits and
 * Op code, meaning: 0 - standard query (QUERY)
 *                   1 - inverse query (IQUERY)
 *                   2 - server status request (STATUS)
 *                3-15 - reserved */
    TRCode m_RCode;
/**< Response code, meaning: 0 - no error
 *                           1 - format error
 *                           2 - server failure
 *                           3 - name error
 *                           4 - not implemented
 *                           5 - refused
 *                        6-15 - reserved */
    char m_QdCount;    /**< 16-bit, # entries in the question section*/
    unsigned int m_AnCount;    /**< 16-bit, # resource records in the answer section*/
    unsigned int m_NsCount;    /**< 16-bit, # name server resource records in the authority section*/
    unsigned int m_ArCount;    /**< 16-bit, # resource records in the additional section*/
    string m_AllCounts;
};

#endif
