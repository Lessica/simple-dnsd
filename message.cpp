/*!
*****************************************************************************
*  \file message.cpp
*
*  \brief   Dns message handling
*
*  All communications inside of the domain protocol are carried inside a
*  message that is divided in 5 sections, some of them can be empty:
*
*    +---------------------+
*    |        Header       |
*    +---------------------+
*    |       Question      | the question for the name server
*    +---------------------+
*    |        Answer       | RRs answering the question
*    +---------------------+
*    |      Authority      | RRs pointing toward an authority
*    +---------------------+
*    |      Additional     | RRs holding additional information
*    +---------------------+
*
*  (Ref: RFC 1035). All the management of this message is done here,
*  including error handling.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#include "message.h"
#include <iostream>
#include <string> 


/*! Constructor
 */
CMessage::CMessage(CLog &log)
        : m_Header(),
          m_Question(),
          m_Answer(),
          m_Authority(),
          m_Additional(),
          m_Host(),
          m_AnswerString(),
          m_AuthorityString(),
          m_AdditionalString(),
          m_Log(log) {
}

/*! Destructor
 */
CMessage::~CMessage() {
}

/*! Sets header section with all the values received 
 */
bool CMessage::setHeader(string &header) {
    unsigned int qd_count;
    bool error = false;
    // more specific error
    CHeader::TRCode error_code;

    // It is not necessary to clean up m_Header
    // as it always will be 12 bytes and it will
    // be overwritten everytime.

    // Id part is not modified so it is not necessary
    // to keep it inside header class

    error_code = m_Header.setOpCodePart((unsigned char) header[2]);
    if (error_code != (CHeader::NO_ERROR)) {
        m_Log.printError("setHeader: error to be returned - ", error_code);
        setErrorCode(error_code);
    }
    // set response code although later
    // it will be modified accordingly
    m_Header.setRCode((unsigned char) header[3]);

    string param = header.substr(4, 8);
    qd_count = m_Header.setAllCounts(param);

    error_code = m_Header.setOpCodePart((unsigned char) header[2]);
    if (error_code != (CHeader::NO_ERROR)) {
        m_Log.printError("setHeader: error to be returned - ", error_code);
        setErrorCode(error_code);
    }
    return error;
}

/*! Gets header section to send a message
 */
void CMessage::getHeader(string &header) {
    string buffer;

    // ID will be the same, but the rest of
    // the sections could be different
    buffer = m_Header.getOpCodePart();
    buffer += m_Header.getRCode();
    buffer += m_Header.getAllCounts();
    header.replace(2, 10, buffer);
}

/*! Sets question section with all the values received
 */
bool CMessage::setQuestion(string &question, unsigned long qLen) {
    unsigned long index = 0;
    unsigned int len = 0;
    string qname, qtype, qclass;
    bool error = false;

    // Get QName section and extract m_Host from it
    // in order to look for IP address within Db.
    index = question.size() - 4;
    qname.erase(0, qname.size());
    qname = question.substr(0, index - 1);

    // Clean up m_Host.
    m_Host.erase(0, m_Host.size());

    // Build hostname from Qname field.
    unsigned int i = 0;
    while (i < qname.size()) {
        len = (unsigned int) qname.at(i);
        m_Host += qname.substr(i + 1, len);
        i += (len + 1);
        if (i < qname.size()) m_Host += ".";
    }
    // Qname should end with a 0
    qname.push_back(0);

    m_Question.setQName(qname);
    qtype = question.substr(index, 2);
    qclass = question.substr(index, 2);

    error = m_Question.setQType(qtype);
    if (error) {
        m_Log.printError("setQuestion: error to be returned - ", CHeader::NOT_IMPLEMENTED);
        setErrorCode(CHeader::NOT_IMPLEMENTED);
        return error;
    }
    error = m_Question.setQClass(qclass);
    if (error) {
        m_Log.printError("setQuestion: error to be returned - ", CHeader::NOT_IMPLEMENTED);
        setErrorCode(CHeader::NOT_IMPLEMENTED);
    }
    return error;
}

/*! Returns the hostname
 */
string &CMessage::getHost() {
    return m_Host;
}

/*! Sets the answer section with the found ip address
 */
bool CMessage::setAnswer(unsigned long addr) {
    bool error = false;

    // Check if addr has been found
    if (addr != 0) {
        // Set AnCount bit to 1, meaning there will be one answer
        m_Header.setAnCount(1);
        m_Answer.setAnswerSection(m_Question.getQName(), m_Question.getQType(), m_Question.getQClass(), addr);
    } else {
        // This server is assumed as authoritative.
        // The address has not been found, meaning that the
        // domain name referenced in the query doesn't exist
        m_Log.printError("setQuestion: error to be returned - ", CHeader::NAME_ERROR);
        setErrorCode(CHeader::NAME_ERROR);
        error = true;
    }
    return error;
}

/*! Gets the answer section 
 */
string &CMessage::getAnswer() {
    m_AnswerString = m_Answer.getAnswerSection();

    return m_AnswerString;
}

/*! Gets the authority section 
 */
string &CMessage::getAuthority() {
    //  m_AuthorityString = m_Authority.getInformation();

    return m_AuthorityString;
}

/*! Gets the additional section
 */
string &CMessage::getAdditional() {
    //  m_AdditionalString = m_Additional.getInformation();

    return m_AdditionalString;
}

/*! Sets Error Code for the response
 */
void CMessage::setErrorCode(unsigned char code) {
    m_Header.setRCode(code);
    // AnCount will be 0 as if there's an error
    // no answer section should be returned.
    m_Header.setAnCount(0);
}
