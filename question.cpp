/*!
*****************************************************************************
*  \file question.cpp
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

#include "question.h"

#include <iostream>
#include <string.h> 

/*! Constructor
 */
CQuestion::CQuestion()
        : m_QName(),
          m_QType(),
          m_QClass() {
}

/*! Destructor
 */
CQuestion::~CQuestion() {
}

void CQuestion::setQName(string &buffer) {
    m_QName.erase(0, m_QName.size());
    m_QName = buffer;
}

string &CQuestion::getQName() {
    return m_QName;
}

bool CQuestion::setQType(string &qType) {
    char value;
    bool error = false;

    m_QType = qType;

    value = (qType[0] << 8) + qType[1];
    // Check that the value is correct
    switch ((CResourceRecord::TQType) value) {
        case (CResourceRecord::A):
        case (CResourceRecord::ALL):
            // Accepted
            break;
        default:
            // Not implemented
            error = true;
            break;
    }
    return error;
}

string &CQuestion::getQType() {
    return m_QType;
}

bool CQuestion::setQClass(string &qClass) {
    unsigned int value;
    bool error = false;

    m_QClass = qClass;

    value = (unsigned int) ((qClass[0] << 8) + qClass[1]);
    // Check that the value is correct, IN & ANY accepted
    error = ((CResourceRecord::TQClass) value == CResourceRecord::CH);
    return error;
}

string &CQuestion::getQClass() {
    return m_QClass;
}
