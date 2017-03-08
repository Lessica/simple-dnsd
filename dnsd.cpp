/*!
*****************************************************************************
*  \file dnsd.cpp
*
*  \brief   Main file for the dns server (standard query support only)
*
*  It opens the communication channel in order to listen forever to the
*  dns port (53) and it keeps reading data from the socket. It creates 
*  the main object that takes care of all the message handling. 
*
*  It also reads the log file from the command line or choses a default one.
*  This log file is created inside /var/log/ directory but some users prefer
*  a different location and that is the reason of accepting it as parameter
*  of the binary file.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#include "dns.h"
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

// Main function
int main(int argc, char **argv) {
    string logFile;

    if (argc == 3) {
        if (strcmp(argv[1], "-f") == 0) {
            string lf(argv[2]);
            logFile = lf;
        } else {
            cerr << "Usage: dnsd -f <log_file>" << endl;
            exit(0);
        }
    } else {
        if (argc == 1) {
            // Default log file
            string lf("/var/log/dnsLog.txt");
            logFile = lf;
        } else {
            cerr << "Usage: dnsd -f <log_file>" << endl;
            exit(0);
        }
    }

    CDns *dns = new CDns((char *) logFile.c_str());

    dns->openCommunication();
    while (1) {
        dns->readMessage();
    }
}
