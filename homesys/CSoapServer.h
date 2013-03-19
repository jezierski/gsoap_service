/* 
 * File:   CSoapServer.h
 * Author: Jezierski
 *
 * Created on 18 marzec 2013, 21:18
 */

#ifndef CSOAPSERVER_H
#define	CSOAPSERVER_H
#include <string>
#include "webservice/soaphomesysService.h"
#include "webservice/homesys.nsmap"


using namespace std;
class CSoapServer{// : public homesysService {
public:
    CSoapServer();
    CSoapServer(const CSoapServer& orig);
    virtual ~CSoapServer();
    
//    int getCurrentTime(string &time);
private:

};

#endif	/* CSOAPSERVER_H */

