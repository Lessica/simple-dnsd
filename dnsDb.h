/*!
*****************************************************************************
*  \file dnsDb.h
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

#ifndef _DNS_DB_H
#define _DNS_DB_H

#include <map>
#include <string>

/*! \class CDnsDb
 *  \brief It takes care of the dns database
 *
 *   CDnsDb reads the information stored withing the configuration file
 *   and keep it inside a map data type. Then everytime it is necessary
 *   to match a hostname with an ip address, this class returns the 
 *   ip address if it has been found inside the db, otherwise it will
 *   return a 0.
 *
 *   A future improvement will be to have alias, meaning more than a
 *   name for the same ip address. For now, the matching is one to one.
 *
 */
using namespace std;

class CDnsDb {
public:
    /*! Constructor
     */
    CDnsDb();

    /*! Destructor
     */
    ~CDnsDb();

    /*! Reads the config file given as parameter. In the file, there
     *  are pairs of IP address and hostnames
     */
    bool readConfigFile(const char *inFile);

    /*! If the hostname is found in the database, the IP address
     *  in long format (compatible to the s_addr field of the
     *  in_addr structure) is returned. If the address has not been
     *  found a 0 is returned.
     */
    unsigned int getAddress(const char *name);

private:
    /*! Comparison
     */
    class less_string {
    public:
        bool operator()(const char *s1, const char *s2) const {
            return strcmp(s1, s2) < 0;
        }
    };

    /*! Parses a line within the file
     */
    void parseLine(char *buffer);

    /*! Data structure to keep the database with all the
     *  information. There is only one pair hostname, ip.
     */
    std::map<const char *, unsigned long int, less_string> m_Db;
};

#endif

