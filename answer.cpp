/*!
*****************************************************************************
*  \file answer.cpp
*
*  \brief   Dns answer section handling
*
*  The system is prepared to have several RRs in order
*  to answer one query, but currently there is only one
*  answer section for each query.
*
*  A future improvement of the system will be to have
*  the authority and additional sections filled at some
*  point. For simple queries, it is not necessary to have
*  them filled up.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#include "answer.h"
#include <iostream>

/////////////////
// Class CAnswer
/////////////////

/*! Constructor
 */
CAnswer::CAnswer()
        : m_RR() {
}

/*! Destructor
 */
CAnswer::~CAnswer() {
}

/*! The calling class sets most of the fields, the rest are decided here.
 * As only internet addresses are taking into account, the length is
 * 4 by definition.
 */
void CAnswer::setAnswerSection(string &name, string &rType, string &rClass, unsigned long addr) {
    string addr_str;

    m_RR.setName(name);
    m_RR.setType(rType);
    m_RR.setClass(rClass);
    // Set to 0
    m_RR.setTTL(0);
    m_RR.setRdLength(4);

    addr_str = (addr >> 24) & 0xff;
    addr_str += (addr >> 16) & 0xff;
    addr_str += (addr >> 8) & 0xff;
    addr_str += addr & 0xff;
    m_RR.setRData(addr_str);
}

/*! Returns values requested by the calling class
 */
string &CAnswer::getAnswerSection() {
    m_RRString.erase(0, m_RRString.size());
    m_RRString = m_RR.getName();
    m_RRString += m_RR.getType();
    m_RRString += m_RR.getClass();
    m_RRString += m_RR.getTTL();
    m_RRString += m_RR.getRdLength();
    m_RRString += m_RR.getRData();

    return m_RRString;
}

// ////////////////////
// // Class CAuthority
// ////////////////////

// constructor
CAuthority::CAuthority()
        : m_Name() {
}

// destructor
CAuthority::~CAuthority() {
}

/////////////////////
// Class CAdditional
/////////////////////

// constructor
CAdditional::CAdditional()
        : m_Name() {
}

// destructor
CAdditional::~CAdditional() {
}
