/* 
 * File:   CCanSimpleSwitchSensor.cpp
 * Author: jezierski
 * 
 * Created on 29 czerwiec 2013, 22:08
 */

#include "CCanSimpleSwitchSensor.h"
#include "CCanSimpleSwitchActor.h"

CCanSimpleSwitchSensor::CCanSimpleSwitchSensor() {
    setDeviceCategory(EDeviceCategory::S_SIMPLE_SWITCH);
    initActionMap();
    log = CLog::getInstance();
}

//CCanSimpleSwitchSensor::CCanSimpleSwitchSensor(const CCanSimpleSwitchSensor& orig) {
//}

CCanSimpleSwitchSensor::~CCanSimpleSwitchSensor() {
}

void CCanSimpleSwitchSensor::initActionMap() {
//    actionMap[CMD_ACTION_TEST] = &CCanSimpleSwitchSensor::actionTest;
//    actionMap[CMD_READ_SENSOR] = &CCanSimpleSwitchSensor::setSwitch;
    
    addFunction(this, CMD_ACTION_TEST, &CCanSimpleSwitchSensor::actionTest);
    addFunction(this, CMD_READ_SENSOR, &CCanSimpleSwitchSensor::setSwitch);
}

void CCanSimpleSwitchSensor::actionTest(SDeviceDescription device, Params params) {
    cout << "action Test SENSOR "<<to_string(device)<<" (";
    for (unsigned int i = 0; i < params.size(); i++)
        cout << (int) params[i] << " ";
    cout << endl;
}

void CCanSimpleSwitchSensor::setSwitch(SDeviceDescription device, Params params) {
    cout << "action setSwitch SENSOR "<<to_string(device)<<" (";
    for (unsigned int i = 0; i < params.size(); i++)
        cout << (int) params[i] << " ";
    cout << endl;
}

