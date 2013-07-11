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


#define CMD_ACTION_TEST 1
#define CMD_READ_SENSOR 2

using namespace std;
class CCanSimpleSwitchSensor : public CDevice{
public:
    CCanSimpleSwitchSensor();
//    CCanSimpleSwitchSensor(const CCanSimpleSwitchSensor& orig);
    virtual ~CCanSimpleSwitchSensor();
    
//    typedef void (CCanSimpleSwitchSensor::*action)(SDeviceDescription, Params);
//    map<int, action> actionMap;
//    void executeFunction(SDeviceDescription, Command, Params);
    
private:
    void actionTest(SDeviceDescription device, Params params);
    void setSwitch(SDeviceDescription device, Params params);
    void initActionMap();
    
    CLog *log;
};

#endif	/* CCANSIMPLESWITCHSENSOR_H */

