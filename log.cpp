/*!
*****************************************************************************
*  \file log.cpp
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

#include "log.h"
#include <iostream>
#include <iomanip>


/*! Constructor
 */
CLog::CLog(char *outFile)
        : m_Fs(outFile, ios::out | ios::binary) {
}

/*! Destructor
 */
CLog::~CLog() {
}

/*! Prints a string in the log file
 */
void CLog::printString(string outString) {
    m_Fs << outString << endl;
}

/*! Prints a formatted string in the log file
 */
void CLog::printFormattedString(string &outString) {
    char s[1];

    for (unsigned int i = 0; i < outString.size(); i++) {
        sprintf(s, "%.2x", (unsigned char) outString[i]);
        m_Fs << "[" << hex << s << "] ";
    }
    m_Fs << dec << " - " << outString.size() << " bytes" << endl;
}

/*! Prints an error in the log file
 */
void CLog::printError(string outString, CHeader::TRCode error_code) {
    string error;

    switch (error_code) {
        case CHeader::FORMAT_ERROR:
            error = "FORMAT_ERROR";
            break;
        case CHeader::SERVER_FAILURE:
            error = "SERVER_FAILURE";
            break;
        case CHeader::NAME_ERROR:
            error = "NAME_ERROR";
            break;
        case CHeader::NOT_IMPLEMENTED:
            error = "NOT_IMPLEMENTED:";
            break;
        case CHeader::REFUSED:
            error = "REFUSED";
            break;
        default:
            error = "NO_ERROR";
            break;
    }
    m_Fs << outString << error << endl;
}
