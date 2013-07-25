#ifndef HOMESYS_H
#define	HOMESYS_H

#include <iostream>
#include <map>

#include "../webservice/homesys.nsmap"
#include "CSoapServer.h"
#include "../can232/CCan232.h"
#include "../tools/CConfiguration.h"
#include "../tools/CDevicesConfig.h"
#include "../tools/CDatabase.h"
#include "CDeviceManager.h"
#include "../tools/CLog.h"
#include "../can_devices/CCanSimpleSwitchActor.h"
#include "../can_devices/CCanSimpleSwitchSensor.h"
#include "CDeviceManager.h"
#include "COperation.h"

using namespace std;

class CApplication{
public:
    CApplication();
    virtual ~CApplication();
    
    void run();
    
private:
    void dbConfig();
    
    CConfiguration *configuration;
    CDevicesConfig *devicesConfig;
    CLog *log;
    
};
#endif
