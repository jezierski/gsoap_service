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
    
    addAction(this, CMD_ACTION_TEST, &CCanSimpleSwitchActor::actionTest);
    addAction(this, CMD_SET_SWITCH, &CCanSimpleSwitchActor::setSwitch);
}

void CCanSimpleSwitchActor::actionTest(SDeviceDescription device, Blob params) {
    cout << "action Test ACTOR "<<to_string(device)<<" (";
    Params par = params["params"].get<Params>();
    for (unsigned int i = 0; i < par.size(); i++)
        cout << (int) par[i] << " ";
    cout << endl;
}

void CCanSimpleSwitchActor::setSwitch(SDeviceDescription device, Blob params) {
    cout << "action setSwitch ACTOR "<<to_string(device)<<" (";
    Params par = params["params"].get<Params>();
    for (unsigned int i = 0; i < par.size(); i++)
        cout << (int) par[i] << " ";
    cout << endl;
}

