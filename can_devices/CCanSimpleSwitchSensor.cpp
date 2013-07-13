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
    
    addAction(this, CMD_ACTION_TEST, &CCanSimpleSwitchSensor::actionTest);
    addAction(this, CMD_READ_SENSOR, &CCanSimpleSwitchSensor::setSwitch);
}

void CCanSimpleSwitchSensor::actionTest(SDeviceDescription device, Blob params) {
    cout << "action Test SENSOR "<<to_string(device)<<" (";
    Params par = params["params"].get<Params>();
    for (unsigned int i = 0; i < par.size(); i++)
        cout << (int) par[i] << " ";
    cout << endl;
}

void CCanSimpleSwitchSensor::setSwitch(SDeviceDescription device, Blob params) {
    cout << "action setSwitch SENSOR "<<to_string(device)<<" (";
    Params par = params["params"].get<Params>();
    for (unsigned int i = 0; i < par.size(); i++)
        cout << (int) par[i] << " ";
    cout << endl;
}

