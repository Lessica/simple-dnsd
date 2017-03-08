/*!
*****************************************************************************
*  \file log.h
*
*  \brief   Display dns log information 
*
*  It prints all information sent by other classes to a log file
*  that can be chosen as a parameter of the program, otherwise
*  a default file is used
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#ifndef _LOG_H
#define _LOG_H

#include "header.h"
#include <string>
#include <fstream>

/*! \class CLog
 *  \brief It prints logging information in a file
 *
 *   CLog prints all the information necessary to understand
 *   what is going on inside the name server
 *
 */
using namespace std;

class CLog {
public:
    /*! Constructor
     */
    CLog(char *outFile);

    /*! Destructor
     */
    ~CLog();

    /*! Prints a string in the log file
     */
    void printString(string outString);

    /*! Prints a formatted string in the log file
     */
    void printFormattedString(string &outString);

    /*! Prints an error in the log file
     */
    void printError(string outString, CHeader::TRCode error_code);

private:
    ofstream m_Fs; /**< Log file used */
};

#endif
