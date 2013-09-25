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
#include "../raspberry/CGPIOClass.h"
#include "../tools/CLog.h"
#include "../tools/CTools.h"
#include "../tools/CParamsConverter.h"
#include "CActionManager.h"


using namespace std;

class CSoapServer : public homesysService {
public:
    CSoapServer();
    //    CSoapServer(const CSoapServer& orig);
    virtual ~CSoapServer();

    void start();

    void assignActionManager(CActionManager* actionManager);


    int getCurrentTime(string &time);
    int getValue(string id, string &result);
    int makeRemoteAction(LONG64 guid, LONG64 luid, LONG64 category, LONG64 command, LONG64 params, LONG64 &result);

    int switchPort(string pinNo, string &result);
private:

    CLog *log;
    CParamsConverter *converter;
    CActionManager *actionManager;
};

#endif	/* CSOAPSERVER_H */

