/* 
 * File:   CCanRGBActor.cpp
 * Author: jezierski
 * 
 * Created on September 11, 2013, 6:16 PM
 */

#include "CCanRGBActor.h"

CCanRGBActor::CCanRGBActor() {
    setDeviceCategory(category);
    initActionMap();

    log = CLog::getInstance();
}

//CCanRGBActor::CCanRGBActor(const CCanRGBActor& orig) {
//}

CCanRGBActor::~CCanRGBActor() {
}

void CCanRGBActor::initActionMap() {
    addAction(this, ACTION_SET_MODE, &CCanRGBActor::setMode);
    addAction(this, ACTION_SET_SPEED, &CCanRGBActor::setSpeed);
    addAction(this, ACTION_SET_CHANNEL_ALL, &CCanRGBActor::setRGB);
    addAction(this, ACTION_SET_CHANNEL_BLUE, &CCanRGBActor::setBlue);
    addAction(this, ACTION_SET_CHANNEL_GREEN, &CCanRGBActor::setGreen);
    addAction(this, ACTION_SET_CHANNEL_RED, &CCanRGBActor::setRed);
    addAction(this, ACTION_GET_SPEED, &CCanRGBActor::getSpeed);
    addAction(this, ACTION_GET_MODE, &CCanRGBActor::getMode);
    addAction(this, ACTION_GET_CHANNEL_RED, &CCanRGBActor::getRed);
    addAction(this, ACTION_GET_CHANNEL_GREEN, &CCanRGBActor::getGreen);
    addAction(this, ACTION_GET_CHANNEL_BLUE, &CCanRGBActor::getBlue);
    addAction(this, ACTION_GET_CHANNEL_ALL, &CCanRGBActor::getRGB);
}

Blob CCanRGBActor::setMode(SDeviceDescription device, Blob params) {
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();
    Blob b;
    string response;
    if (par.size() == 0) {
        response = "RGBActor->setMode->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    cout << "set mode: " << (int) par[0] << endl;
    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_MODE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setMode->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;

}

Blob CCanRGBActor::setSpeed(SDeviceDescription device, Blob params) {
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();
    Blob b;
    string response;
    if (par.size() == 0) {
        response = "RGBActor->setSpeed->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_SPEED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setSpeed->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanRGBActor::getSpeed(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_SPEED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        values.push_back(buffer[OFFSET_DATA]);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " SPEED: " + to_string(values[0]) );
    }else{
        response = "RGBActor->getSpeed->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::setRed(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();
    Blob b;
    string response;
    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_RED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setRed->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);

    return b;
}

Blob CCanRGBActor::getRed(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_CHANNEL_RED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        long long val = buffer[OFFSET_DATA] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 1];
        values.push_back(val);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " CHANNEL_RED: " + to_string(values[0]) );
    }else{
        response = "RGBActor->getRed->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::getGreen(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_CHANNEL_GREEN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        long long val = buffer[OFFSET_DATA] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 1];
        values.push_back(val);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " CHANNEL_GREEN: " + to_string(values[0]) );
    }else{
        response = "RGBActor->getGreen->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::getBlue(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_CHANNEL_BLUE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        long long val = buffer[OFFSET_DATA] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 1];
        values.push_back(val);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " CHANNEL_BLUE: " + to_string(values[0]) );
    }else{
        response = "RGBActor->getBlue->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::getMode(SDeviceDescription device, Blob params) {
    //    cout << "action getSensorSwitch SENSOR "<<to_string(device)<<endl;
    CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_MODE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        long long val = buffer[OFFSET_DATA] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 1];
        values.push_back(val);
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " MODE: " + to_string(values[0]) );
    }else{
        response = "RGBActor->getMode->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::setGreen(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();
    CCanBuffer buffer;
    Blob b;
    string response;
    buffer.insertCommand(CMD_SET_CHANNEL_GREEN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setGreen->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::setBlue(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();
    Blob b;
    string response;
    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_BLUE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setBlue->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::setRGB(SDeviceDescription device, Blob params) {
    vector<unsigned int> values = params[BLOB_RGB_ALL].get < vector<unsigned int >> ();
    Blob b;
    string response;
    if (values.size() != 3) {
        response = "SimpleSwitchActor->setRGB->Incorrect params";
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (values[0] & 0xfff);
    buffer << (unsigned char) (values[1] >> 4);
    buffer << (unsigned char) (((values[1] << 4) & 0xf0) | ((values[2] >> 8) & 0x0f));
    buffer << (unsigned char) (values[2] & 0xff);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "RGBActor->setRGB->Sending CAN frame failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CCanRGBActor::getRGB(SDeviceDescription device, Blob params) {
     CCanBuffer buffer;
    Blob b;
    string response;
    vector<long long> values;
    buffer.insertCommand(CMD_GET_CHANNEL_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer.buildBuffer();
    buffer = getProtocol()->request(buffer);
    if (buffer.getLength() > 0) {
        response = "OK";
        long long val = buffer[OFFSET_DATA] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 1];
        values.push_back(val);  //RED
        val =  buffer[OFFSET_DATA + 2] & 0xff;
        val <<= 4;
        val &= 0xff0;
        val|= ((buffer[OFFSET_DATA + 3] & 0xf0) >> 4);
        values.push_back(val);  //GREEN
        val = buffer[OFFSET_DATA + 3] & 0x0f;
        val <<= 8;
        val |= buffer[OFFSET_DATA + 4];
        values.push_back(val);  //BLUE
        
        b[BLOB_RESPONSE_INT_VALUES].put<vector<long long>>(values);
        log->info("Device " + to_string(device) + " CHANNEL_ALL R: " + to_string(values[0]) + ", G: " +  to_string(values[1]) + ", B: " +to_string(values[2]));
    }else{
        response = "RGBActor->getRGB->Receiving CAN frame failed";
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}