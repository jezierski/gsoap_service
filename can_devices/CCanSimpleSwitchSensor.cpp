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

    addAction(this, ACTION_READ_SENSOR_STATUS, &CCanSimpleSwitchSensor::getSwitchStatus);
}

Blob CCanSimpleSwitchSensor::getSwitchStatus(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    buffer.insertCommand(CMD_READ_SENSOR);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = (buffer[2] > 0) ? "1" : "0";
        log->info("Device " + to_string(device) + " STATUS: " + to_string((int) buffer[2]));
    }else{
        response = "SimpleSwitchSensor->getSwitchStatus->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

