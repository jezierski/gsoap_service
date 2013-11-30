/* 
 * File:   CCanSimpleSwitch.cpp
 * Author: jezierski
 * 
 * Created on 10 czerwiec 2013, 20:55
 */

#include "CCanSimpleSwitchActor.h"

CCanSimpleSwitchActor::CCanSimpleSwitchActor() {
    //    setDeviceCategory(EDeviceCategory::A_SIMPLE_SWITCH);
    setDeviceCategory(category);
    initActionMap();

    log = CLog::getInstance();
}

//CCanSimpleSwitch::CCanSimpleSwitch(const CCanSimpleSwitch& orig) {
//}

CCanSimpleSwitchActor::~CCanSimpleSwitchActor() {
}

void CCanSimpleSwitchActor::initActionMap() {
    addAction(this, ACTION_SET_OUTPUT, &CCanSimpleSwitchActor::setOutput);
    addAction(this, ACTION_GET_OUTPUT, &CCanSimpleSwitchActor::getActorStatus);
}

Blob CCanSimpleSwitchActor::setOutput(SDeviceDescription device, Blob params) {
//    cout << "action setOutput " << to_string(device) <<endl;
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();
    string response;
    Blob b;
    
    if (par.size() == 0) {
        response = "SimpleSwitchActor->setOutput->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_PIN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "SimpleSwitchActor->setOutput->Sending CAN frame failed";
    
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
   
}

Blob CCanSimpleSwitchActor::getActorStatus(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_READ_ACTOR);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        values.push_back(buffer[OFFSET_DATA]);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " OUTPUT STATE: " + to_string(values[0]) );
    }else{
        response = "SimpleSwitchActor->getActorStatus->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
    
}



