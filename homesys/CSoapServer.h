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
#include "CDeviceManager.h"
#include <fstream>


using namespace std;

class CSoapServer : public homesysService {
public:
    CSoapServer();
    //    CSoapServer(const CSoapServer& orig);
    virtual ~CSoapServer();

    void start();

    void assignDeviceManager(CDeviceManager* deviceManager);


    int setDeviceName(ns1__SDeviceDescription *device, std::string name, std::string &response);
    int getXML(string id, string &result);
    int saveXML(std::string id, std::string body, std::string &result);
    int makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &_param_1);
    int getDevicesList(LONG64 category, struct ns1__getDevicesListResponse &_param_1);
    
    int switchPort(string pinNo, string &result);
    
    Signal0<void> operationLoad;
private:

    string readFile(string filename);
    CLog *log;
    CParamsConverter *converter;
    CDeviceManager *deviceManager;
};

#endif	/* CSOAPSERVER_H */

