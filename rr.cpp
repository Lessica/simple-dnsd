/*!
*****************************************************************************
*  \file rr.cpp
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

#include "rr.h"
#include <iostream>

// constructor
CResourceRecord::CResourceRecord()
        : m_Name(),
          m_Type(),
          m_Class(),
          m_TTL(),
          m_RdLength(),
          m_RData() {
}

// destructor
CResourceRecord::~CResourceRecord() {
}

void CResourceRecord::setName(string &buffer) {
    // variable size
    m_Name.erase(0, m_Name.size());
    m_Name = buffer;
}

string &CResourceRecord::getName() {
    return m_Name;
}

void CResourceRecord::setType(string &rType) {
    // fixed size (2 bytes)
    m_Type = rType;
}

string &CResourceRecord::getType() {
    return m_Type;
}

void CResourceRecord::setClass(string &rClass) {
    // fixed size (2 bytes)
    m_Class = rClass;
}

string &CResourceRecord::getClass() {
    return m_Class;
}

void CResourceRecord::setTTL(unsigned int ttl) {
    // fixed size (4 bytes)
    m_TTL = (ttl >> 24) & 0xff;
    m_TTL += (ttl >> 16) & 0xff;
    m_TTL += (ttl >> 8) & 0xff;
    m_TTL += ttl & 0xff;
}

string &CResourceRecord::getTTL() {
    return m_TTL;
}

void CResourceRecord::setRdLength(unsigned int rdLength) {
    // fixed size (2 bytes)
    m_RdLength = (rdLength >> 8) & 0xff;
    m_RdLength += rdLength & 0xff;
}

string &CResourceRecord::getRdLength() {
    return m_RdLength;
}

void CResourceRecord::setRData(string &rData) {
    //  m_RData.erase(0, m_RData.size());
    // fixed size (4 bytes)
    m_RData = rData;
}

string &CResourceRecord::getRData() {
    return m_RData;
}
