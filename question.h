/*!
*****************************************************************************
*  \file question.h
*
*  \brief   Dns question section handling
*
*  The question section format is the following one:
*
*                                   1  1  1  1  1  1
*      0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                                               |
*    /                     QNAME                     /
*    /                                               /
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                     QTYPE                     |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*    |                     QCLASS                    |
*    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
*
*  (Ref: RFC 1035) and CQuestion handles error checking
*  and storage of all these fields.
*
*  Currently only one question section is considered but
*  the data structure is prepared for future improvements.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#ifndef _QUESTION_H
#define _QUESTION_H

#include "rr.h"
#include <string>

/*! \class CQuestion
 *  \brief It takes care of all related to question section handling
 *
 *   Description
 *
 */
using namespace std;

class CQuestion {
public:

    /*! Constructor
     */
    CQuestion();

    /*! Destructor
     */
    ~CQuestion();

    void setQName(string &buffer);

    string &getQName();

    bool setQType(string &qType);

    string &getQType();

    bool setQClass(string &qClass);

    string &getQClass();

private:
    string m_QName;  /**< defines QName field */
    string m_QType;  /**< defines QType field */
    string m_QClass; /**< defines QClass field */
};

#endif
