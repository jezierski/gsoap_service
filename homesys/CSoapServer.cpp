/* 
 * File:   CSoapServer.cpp
 * Author: Jezierski
 * 
 * Created on 18 marzec 2013, 21:18
 */

#include "CSoapServer.h"

CSoapServer::CSoapServer() {
    log = CLog::getInstance();
    converter = CParamsConverter::getInstance();
}

//CSoapServer::CSoapServer(const CSoapServer& orig) {
//}

CSoapServer::~CSoapServer() {
}

void CSoapServer::assignDeviceManager(CDeviceManager* deviceManager) {
    this->deviceManager = deviceManager;
}

int CSoapServer::getCurrentTime(string& currentTime) {
    time_t rawtime;
    time(&rawtime);
    string strTime(ctime(&rawtime));
    currentTime = strTime;
    return SOAP_OK;
}

int CSoapServer::getValue(string id, string &result) {
    result = "Text etnered: " + id;
    return SOAP_OK;
}

int CSoapServer::switchPort(string pinNo, string &result) {
    static int portState = 0;
    CGPIOClass gpio(pinNo);
    gpio.export_gpio();
    gpio.setdir_gpio("out");
    if (portState) {
        portState = 0;
        gpio.setval_gpio("0");
        result = "OK_0";
        std::cout << "port " << pinNo << " OFF" << std::endl;
    } else {
        portState = 1;
        gpio.setval_gpio("1");
        result = "OK_1";
        std::cout << "port " << pinNo << " ON" << std::endl;
    }
    gpio.unexport_gpio();

    return SOAP_OK;
}

int CSoapServer::makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, string &result) {
    SAction action;
    action.command = command;
    action.params = converter->use(device->category, command, params);
    action.device.category = static_cast<EDeviceCategory>(device->category);
    action.device.guid = device->GUID;
    action.device.luid = device->LUID;
    Blob b = deviceManager->invokeRemoteAction(action.device, action.command, action.params);
    result = b[BLOB_TXT_RESPONSE].get<string>();
//    actionManager->addAction(action);
//    delete device;
    cout << "makeRemoteAction, guid: " << device->GUID << ", luid: " << device->LUID << ", cat: " << device->category << ", comm: " << command << endl;
    return 0;
}


void CSoapServer::start() {
    int error;
    while (1) {
        error = run(1234);
        if (error != SOAP_OK)
            log->error("SOAP server error code: " + to_string(error));
    }
}

