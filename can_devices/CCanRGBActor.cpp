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
}

void CCanRGBActor::setMode(SDeviceDescription device, Blob params) {
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();

    if (par.size() != 1) {
        log->error("Action [setMode] incorrect params");
        return;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_MODE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}

void CCanRGBActor::setSpeed(SDeviceDescription device, Blob params) {
    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();
    if (par.size() != 1) {
        log->error("Action [setSpeed] incorrect params");
        return;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_SPEED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (unsigned char) par[0];
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}

void CCanRGBActor::setRed(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_RED);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}

void CCanRGBActor::setGreen(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_GREEN);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}

void CCanRGBActor::setBlue(SDeviceDescription device, Blob params) {
    unsigned int value = params[BLOB_RGB_CHANNEL].get<unsigned int>();

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_BLUE);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (value & 0xfff);
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}
void CCanRGBActor::setRGB(SDeviceDescription device, Blob params) {
    vector<unsigned int> values = params[BLOB_RGB_ALL].get<vector<unsigned int>>();

    if (values.size() != 3) {
        log->error("Action [setRGB] incorrect params");
        return;
    }

    CCanBuffer buffer;

    buffer.insertCommand(CMD_SET_CHANNEL_ALL);
    buffer.insertId((unsigned char) getDeviceCategory());
    buffer << (unsigned char) getAddress(device);
    buffer << (values[0] & 0xfff);
    buffer << (unsigned char)(values[1] >> 4);
    buffer << (unsigned char)(((values[1] << 4) & 0xf0) | ((values[2] >> 8) & 0x0f));
    buffer << (unsigned char)(values[2] & 0xff);
    buffer.buildBuffer();
    getProtocol()->send(buffer);
   
}