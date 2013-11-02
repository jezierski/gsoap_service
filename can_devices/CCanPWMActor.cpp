/* 
 * File:   CCanPWMActor.cpp
 * Author: jezierski
 * 
 * Created on November 2, 2013, 3:10 PM
 */

#include "CCanPWMActor.h"

CCanPWMActor::CCanPWMActor() {
    setDeviceCategory(category);
    initActionMap();

    log = CLog::getInstance();
}

//CCanPWMActor::CCanPWMActor(const CCanPWMActor& orig) {
//}

CCanPWMActor::~CCanPWMActor() {
}

void CCanPWMActor::initActionMap() {
    addAction(this, ACTION_SET_PWM, &CCanPWMActor::setPWM);
    addAction(this, ACTION_SET_PWM_ALL, &CCanPWMActor::setAllPWM);
    addAction(this, ACTION_SET_PWM_ALL_THE_SAME, &CCanPWMActor::setAllTheSamePWM);
    addAction(this, ACTION_PWM_UP, &CCanPWMActor::increasePWM);
    addAction(this, ACTION_PWM_UP_ALL, &CCanPWMActor::increaseAllPWM);
    addAction(this, ACTION_PWM_DOWN, &CCanPWMActor::decreasePWM);
    addAction(this, ACTION_PWM_DOWN_ALL, &CCanPWMActor::decreaseAllPWM);
    addAction(this, ACTION_GET_PWM, &CCanPWMActor::getPWM);
}

Blob CCanPWMActor::setPWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_VALUE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;

    if (value.size() == 0) {
        response = "PWMActor->setPWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_SET_PWM);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->setPWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::getPWM(SDeviceDescription device, Blob params) {
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_PWM);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        unsigned char value = buffer[OFFSET_DATA];
        values.push_back(value);
        b[BLOB_RESPONSE_INT_VALUES].put < vector<long long >> (values);
        log->info("Device " + to_string(device) + " PWM_VALUE: " + to_string(values[0]));
    } else {
        response = "PWMActor->getPWM->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanPWMActor::increasePWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_CHANGE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (value.size() == 0) {
        response = "PWMActor->increasePWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_PWM_UP);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->increasePWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::decreasePWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_CHANGE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (value.size() == 0) {
        response = "PWMActor->decreasePWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_PWM_DOWN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->decreasePWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::setAllPWM(SDeviceDescription device, Blob params) {
    Params values = params[BLOB_ACTION_PARAMETER].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (values.size() == 0) {
        response = "PWMActor->setAllPWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_SET_PWM_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    for (unsigned char val : values) {
        buffer << (unsigned char) (val);
    }
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->setAllPWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::setAllTheSamePWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_VALUE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (value.size() == 0) {
        response = "PWMActor->setAllTheSamePWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_SET_PWM_ALL_THE_SAME);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->setAllTheSamePWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::increaseAllPWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_CHANGE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (value.size() == 0) {
        response = "PWMActor->increaseAllPWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_PWM_UP_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->increaseAllPWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanPWMActor::decreaseAllPWM(SDeviceDescription device, Blob params) {
    Params value = params[BLOB_PWM_CHANGE].get<Params>();
    Blob b;
    string response;
    CCanBuffer buffer;
    if (value.size() == 0) {
        response = "PWMActor->decreaseAllPWM->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    buffer.insertCommand(CMD_PWM_DOWN_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) (value[0]);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "PWMActor->decreaseAllPWM->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}