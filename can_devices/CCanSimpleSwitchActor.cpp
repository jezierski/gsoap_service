/* 
 * File:   CCanSimpleSwitch.cpp
 * Author: jezierski
 * 
 * Created on 10 czerwiec 2013, 20:55
 */

#include "CCanSimpleSwitchActor.h"

CCanSimpleSwitchActor::CCanSimpleSwitchActor() {
    //    setDeviceCategory(EDeviceCategory::A_SIMPLE_SWITCH);
    setDeviceCategory(EDeviceCategory::A_SIMPLE_SWITCH);
    initActionMap();

    log = CLog::getInstance();
}

//CCanSimpleSwitch::CCanSimpleSwitch(const CCanSimpleSwitch& orig) {
//}

CCanSimpleSwitchActor::~CCanSimpleSwitchActor() {
}

void CCanSimpleSwitchActor::initActionMap() {
//    actionMap[CMD_ACTION_TEST] = &CCanSimpleSwitchActor::actionTest;
//    actionMap[CMD_SET_SWITCH] = &CCanSimpleSwitchActor::setSwitch;
    
    addFunction(this, CMD_ACTION_TEST, &CCanSimpleSwitchActor::actionTest);
    addFunction(this, CMD_SET_SWITCH, &CCanSimpleSwitchActor::setSwitch);
}

void CCanSimpleSwitchActor::actionTest(SDeviceDescription device, Params params) {
    cout << "action Test ACTOR "<<to_string(device)<<" (";
    for (unsigned int i = 0; i < params.size(); i++)
        cout << (int) params[i] << " ";
    cout << endl;
}

void CCanSimpleSwitchActor::setSwitch(SDeviceDescription device, Params params) {
    cout << "action setSwitch ACTOR "<<to_string(device)<<" (";
    for (unsigned int i = 0; i < params.size(); i++)
        cout << (int) params[i] << " ";
    cout << endl;
}

