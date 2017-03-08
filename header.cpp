/*!
*****************************************************************************
*  \file header.cpp
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

#include "header.h"
#include <iostream>

/*! Constructor
 */
CHeader::CHeader()
        : m_OpCodePart(0),
          m_RCode(NO_ERROR),
          m_QdCount(0),
          m_AnCount(0),
          m_NsCount(0),
          m_ArCount(0),
          m_AllCounts() {
}

/*! Destructor
 */
CHeader::~CHeader() {
}

CHeader::TRCode CHeader::setOpCodePart(unsigned char c) {
    int qr;
    int op_code;
    int tc;

    m_OpCodePart = c;

    qr = (c >> 7) & 0x01;
    op_code = (c >> 3 & 0x0f);
    tc = (c >> 1) & 0x01;

    // QR should be 1 in the response, not
    // inside the query. It's a format error.
    if (qr == 1) return FORMAT_ERROR;
    else qr = 0x01;

    // The name server only accepts standard queries
    if (op_code != 0) {
        return NOT_IMPLEMENTED;
    }

    // The name server does not accept truncated requests
    if (tc != 0) {
        return NOT_IMPLEMENTED;
    }
    // If RD set, RA=0 will be returned so nothing will be done.
    return NO_ERROR;
}

unsigned char CHeader::getOpCodePart() {
    // Setting response (QR=1)
    m_OpCodePart = (unsigned char) ((1 << 7) + m_OpCodePart);

    // Normal use, it should be 81
    return m_OpCodePart;
}

void CHeader::setRCode(unsigned char c) {
    m_RCode = (TRCode) c;
    // Z field will be ignored (and assume it's always 0).
}

unsigned char CHeader::getRCode() {
    return (unsigned char) m_RCode;
}

CHeader::TRCode CHeader::setAllCounts(string &buffer) {
    // fixed size (8 bytes)
    m_AllCounts = buffer;

    m_QdCount = (buffer[0] << 8) + buffer[1];
    // Check value
    if (m_QdCount == 0)
        return FORMAT_ERROR;
    if (m_QdCount > 1) {
        return NOT_IMPLEMENTED;
    }
    // no errors
    return NO_ERROR;
}

string &CHeader::getAllCounts() {
    // m_AnCount has been set previously set

    // For now these 2 fiels are always 0 although
    // the structure is prepared for the future
    m_NsCount = 0;
    m_ArCount = 0;

    // we'll only modify the last 6 bytes,
    // m_QdCount should be the same one
    m_AllCounts[2] = (char) ((m_AnCount >> 8) & 0xff);
    m_AllCounts[3] = (char) (m_AnCount & 0xff);
    m_AllCounts[4] = (char) ((m_NsCount >> 8) & 0xff);
    m_AllCounts[5] = (char) (m_NsCount & 0xff);
    m_AllCounts[6] = (char) ((m_ArCount >> 8) & 0xff);
    m_AllCounts[7] = (char) (m_ArCount & 0xff);

    return m_AllCounts;
}

/*! Used mostly during the error management 
 *  Otherwise it will updated to 1 when 
 *  sending the response
 */
void CHeader::setAnCount(unsigned int anCount) {
    m_AnCount = anCount;
}
