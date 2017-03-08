/*!
*****************************************************************************
*  \file answer.h
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

#ifndef _ANSWER_H
#define _ANSWER_H

#include "rr.h"

/////////////////
// Class CAnswer
/////////////////

/*! \class CAnswer
 *  \brief It takes care of all related to answer section handling
 *
 *   Description
 *
 */
using namespace std;

class CAnswer {
public:

    /*! Constructor
     */
    CAnswer();

    /*! Destructor
     */
    ~CAnswer();

    /*! The calling class sets most of the fields, the rest are decided here.
     * As only internet addresses are taking into account, the length is
     * 4 by definition.
     */
    void setAnswerSection(string &name, string &rType, string &rClass, unsigned long addr);

    /*! Returns values requested by the calling class
     */
    string &getAnswerSection();

private:
    // For now, I'll have only one RR
    CResourceRecord m_RR;       /**< Resource Record for the current answer */
    string m_RRString; /**< String to be returned to upper levels */
};


////////////////////
// Class CAuthority
////////////////////

/*! \class CAuthority
 *  \brief It takes care of all related to authority section handling
 *
 *   Description
 *
 */
class CAuthority {
public:

    // constructor
    CAuthority();

    // destructor
    ~CAuthority();

private:
    string m_Name;
};

/////////////////////
// Class CAdditional
/////////////////////

/*! \class CAdditional
 *  \brief It takes care of all related to additional section handling
 *
 *   Description
 *
 */
class CAdditional {
public:

    // constructor
    CAdditional();

    // destructor
    ~CAdditional();

private:
    string m_Name;
};

#endif
