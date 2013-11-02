#ifndef HOMESYS_H
#define	HOMESYS_H

#include <iostream>
#include <map>
#include <thread>

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
#include "../can_devices/CCanRGBActor.h"
#include "../can_devices/CCanPWMActor.h"
#include "CDeviceManager.h"
#include "CActionTranslator.h"
#include "CTimer.h"

using namespace std;

class CApplication{
public:
    CApplication();
    virtual ~CApplication();
    
    void run();
    
private:
    void dbConfig();
    void assignSlots();
    
    CConfiguration *configuration;
    CDevicesConfig *devicesConfig;
    CActionTranslator *actionTranslator;
    CDeviceManager *deviceManager;
    CTimer *timer;
    CCan232 * can232device;
    CLog *log;
    CSoapServer *soapServer;
    
};
#endif
