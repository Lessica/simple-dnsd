/*!
*****************************************************************************
*  \file dnsDb.cpp
*
*  \brief   Dns database. 
*
*  It creates and mantains a structure to keep all information included
*  inside a file "/etc/hosts" style. It also accepts request queries of it.
*
*  \version 0.1
*  \date    11-September-2006
*  \author  Cristina Camacho Romaguera
*
*****************************************************************************
*/

#include "dnsDb.h"

#include <iostream>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>

/*! Constructor
 */
CDnsDb::CDnsDb()
        : m_Db() {
}

/*! Destructor
 */
CDnsDb::~CDnsDb() {
}

/*! Reads the config file given as parameter. In the file, there
 *  are pairs of IP address and hostnames 
 */
bool CDnsDb::readConfigFile(const char *inFile) {
    bool error = false;

    char buffer[128];
    ifstream fs(inFile, ios::in | ios::binary);

    if (fs) {
        // Config file opened correctly
        do {
            fs.getline(reinterpret_cast<char *>(&buffer), 128);
            parseLine(buffer);
        } while (!fs.eof());
        fs.close();
    } else {
        error = true;
    }
    return error;
}


/*! If the hostname is found in the database, the IP address
 *  in long format (compatible to the s_addr field of the 
 *  in_addr structure) is returned. If the address has not been
 *  found a 0 is returned.
 */
in_addr_t CDnsDb::getAddress(const char *name) {
    map<const char *, unsigned long int, less_string>::iterator it = m_Db.find(name);

    if (it == m_Db.end()) {
        return 0;
    } else {
        return (in_addr_t) (*it).second;
    }
}

/*! Parses a line within the file
 */
void CDnsDb::parseLine(char *buffer) {
    string strAux(buffer);
    unsigned long ind_end;
    unsigned long ind_beg;
    string address, *name;
    bool address_found = false;
    struct in_addr inp;

    do {
        address.erase();
        // skip all possible spaces , ind_beg points to the first element
        ind_beg = strAux.find_first_not_of(" ");
        // from the first element, I am looking for the next space, then I will have the first string
        ind_end = strAux.find_first_of(" ", ind_beg);
        // address it now contains the IP address
        if (ind_beg == ind_end) {
            // blank line
            return;
        }
        address.append(strAux.substr(ind_beg, ind_end));
        if (address[0] == '#') {
            // skip this line as it's a comment
            return;
        }
        if (inet_aton(address.data(), &inp)) {
            address_found = true;
        }
    } while (!address_found);

    // Now the the IP address has been found and I'm keeping the hostname
    // For now, let's assume there is only one name for each IP address
    ind_beg = strAux.find_first_not_of(" ", ind_end + 1);
    ind_end = strAux.find_first_of(" ", ind_beg);
    name = new string(strAux.substr(ind_beg, ind_end));
    m_Db[name->c_str()] = inp.s_addr;
}
