/*!
*****************************************************************************
*  \file message.h
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

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "header.h"
#include "question.h"
#include "answer.h"
#include "log.h"

/*! \class CMessage
 *  \brief It takes care of all related to message handling
 *
 *   CMessage keeps the necessary information to manage the query
 *   received by CDns. It relies on other classes to keep the header
 *   section, question section and so on. It also replies with the
 *   information requested by CDns to build the dns response.
 *
 */
using namespace std;

class CMessage {
public:
    /*! Constructor
     */
    CMessage(CLog &log);

    /*! Destructor
     */
    ~CMessage();

    /*! Sets header section with all the values received
     */
    bool setHeader(string &header);

    /*! Gets header section to send a message
     */
    void getHeader(string &header);

    /*! Sets question section with all the values received
     */
    bool setQuestion(string &question, unsigned long qLen);

    /*! Gets question section to send a message
     */
    unsigned int getQuestion(string &question);

    /*! Returns the hostname
     */
    string &getHost();

    /*! Sets the answer section with the found ip address
     */
    bool setAnswer(long unsigned addr);

    /*! Gets the answer section
     */
    string &getAnswer();

    /*! Gets the authority section
     */
    string &getAuthority();

    /*! Gets the additional section
     */
    string &getAdditional();

private:
    /*! Sets Error Code for the response
     */
    void setErrorCode(unsigned char code);

    CHeader m_Header;           /**<  CHeader class */
    CQuestion m_Question;         /**<  CQuestion class */
    CAnswer m_Answer;           /**<  CAnswer class */
    CAuthority m_Authority;        /**<  CAuthority class */
    CAdditional m_Additional;       /**<  CAdditional class */
    string m_Host;             /**<  Host requested within the query */
    string m_AnswerString;     /**<  Answer string to deliver to CDns */
    string m_AuthorityString;  /**<  Authority string to deliver to CDns */
    string m_AdditionalString; /**<  Additional string to deliver to CDns */
    CLog &m_Log;              /**<  Log file class */
};

#endif
