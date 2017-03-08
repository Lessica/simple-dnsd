/*!
*****************************************************************************
*  \file rr.h
*
*  \brief   Dns resource record handling
*
*  The resource record format is the following one:
*
*                                    1  1  1  1  1  1
*      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                                               |
*    /                                               /
*    /                      NAME                     /
*    |                                               |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                      TYPE                     |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                     CLASS                     |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                      TTL                      |
*    |                                               |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                   RDLENGTH                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
*    /                     RDATA                     /
*    /                                               /
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*
*  (Ref: RFC 1035). And all this information is handled here.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#ifndef _RR_H
#define _RR_H

#include <string>

/*! \class CResourceReacord
 *  \brief It takes care of all related to resource records
 *
 *   Description
 *
 */
using namespace std;

class CResourceRecord {
public:

    // constructor
    CResourceRecord();

    // destructor
    ~CResourceRecord();

    void setName(string &buffer);

    string &getName();

    void setType(string &rType);

    string &getType();

    void setClass(string &rClass);

    string &getClass();

    void setTTL(unsigned int ttl);

    string &getTTL();

    void setRdLength(unsigned int rdLength);

    string &getRdLength();

    void setRData(string &rData);

    string &getRData();

    /* I will only create the superset QType and QClass and I will use it
       also for Type and Class resource record fields, as I am controlling
       the response it shouldn't be any incompatibility.
    */
    /* These types are defined in RFC 1035 */
    /* This program does not support ipv6, which is defined in RFC 3596:
     * https://www.ietf.org/rfc/rfc3596.txt */
    enum TQType {
        A = 1,   /**< a host address */
        NS = 2,
        MD = 3,   /**< obsolete */
        MF = 4,   /**< obsolete */
        CNAME = 5,
        SOA = 6,
        MB = 7,
        MG = 8,
        MR = 9,
        NLL = 10,
        WKS = 11,
        PTR = 12,
        HINFO = 13,
        MINFO = 14,
        MX = 15,
        TXT = 16,
        AXFR = 252,
        MAILB = 253,
        MAILA = 254,
        ALL = 255  /**< all records */
    };
    /* These types are defined in RFC 1035 */
    enum TQClass {
        IN = 1,     /**< the internet */
        CH = 3,
        ANY = 255    /**< any class */
    };

private:
    string m_Name;     /**< defines Name field */
    string m_Type;     /**< defines Type field */
    string m_Class;    /**< defines Class field */
    string m_TTL;      /**< defines TTL field */
    string m_RdLength; /**< defines RdLength field */
    string m_RData;    /**< defines RData field */
};

#endif
