/* 
 * File:   CCanSimpleSwitchSensor.h
 * Author: jezierski
 *
 * Created on 29 czerwiec 2013, 22:08
 */

#ifndef CCANSIMPLESWITCHSENSOR_H
#define	CCANSIMPLESWITCHSENSOR_H


#include "../homesys/CDevice.h"
#include "../tools/CCanBuffer.h"
#include "CCanConstans.h"


#define ACTION_READ_SENSOR_STATUS 101
#define CMD_READ_SENSOR 101

using namespace std;
class CCanSimpleSwitchSensor : public CDevice{
public:
    CCanSimpleSwitchSensor();
//    CCanSimpleSwitchSensor(const CCanSimpleSwitchSensor& orig);
    virtual ~CCanSimpleSwitchSensor();
    
//    typedef void (CCanSimpleSwitchSensor::*action)(SDeviceDescription, Params);
//    map<int, action> actionMap;
//    void executeAction(SDeviceDescription, Command, Params);
    
private:
    Blob getSwitchStatus(SDeviceDescription device, Blob params);
    void initActionMap();
    
    CLog *log;
};

#endif	/* CCANSIMPLESWITCHSENSOR_H */

