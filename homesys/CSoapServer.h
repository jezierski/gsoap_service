/* 
 * File:   CSoapServer.h
 * Author: Jezierski
 *
 * Created on 18 marzec 2013, 21:18
 */

#ifndef CSOAPSERVER_H
#define	CSOAPSERVER_H
#include <string>
#include <time.h>
#include "../webservice/soaphomesysService.h"



using namespace std;
class CSoapServer : public homesysService {
public:
    CSoapServer();
    CSoapServer(const CSoapServer& orig);
    virtual ~CSoapServer();
    
    void start();
    int getCurrentTime(string &time);
    int getValue(string id, string &result);
private:

};

#endif	/* CSOAPSERVER_H */

