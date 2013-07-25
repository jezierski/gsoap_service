/* 
 * File:   CCanSimpleSwitch.cpp
 * Author: jezierski
 * 
 * Created on 10 czerwiec 2013, 20:55
 */

#include "CCanSimpleSwitchActor.h"

CCanSimpleSwitchActor::CCanSimpleSwitchActor() {
    //    setDeviceCategory(EDeviceCategory::A_SIMPLE_SWITCH);
    setDeviceCategory(CATEGORY);
    initActionMap();

    log = CLog::getInstance();
}

//CCanSimpleSwitch::CCanSimpleSwitch(const CCanSimpleSwitch& orig) {
//}

CCanSimpleSwitchActor::~CCanSimpleSwitchActor() {
}

void CCanSimpleSwitchActor::initActionMap() {
    addAction(this, ACTION_SET_OUTPUT, &CCanSimpleSwitchActor::setOutput);
}

void CCanSimpleSwitchActor::setOutput(SDeviceDescription device, Blob params) {
    cout << "action setOutput " << to_string(device) << " (";
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();

    if (par.size() != 1) {
        log->error("Action [setOutput] incorrect params");
        return;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_PIN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    getProtocol()->sendCanFrame(buffer);
   
}



