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

int CSoapServer::makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse &response) {
    SAction action;
    action.command = command;
    action.params = converter->use(device->category, command, params);
    action.device.category = static_cast<EDeviceCategory>(device->category);
    action.device.guid = device->GUID;
    action.device.luid = device->LUID;
    Blob b = deviceManager->invokeRemoteAction(action.device, action.command, action.params);
    vector<LONG64>values = b[BLOB_RESPONSE_INT_VALUES].get<vector<LONG64>>();
    
    struct ns1__makeRemoteActionResponse responseTemp;
    responseTemp.response = new ns1__responseType();
    responseTemp.response->result = b[BLOB_TXT_RESPONSE_RESULT].get<string>();
    responseTemp.response->values = new ns1__valuesType();
    responseTemp.response->values->responseMessage = b[BLOB_TXT_RESPONSE_MSG].get<string>();
    responseTemp.response->values->numValues = values.size();
    responseTemp.response->values->values = new ns1__valueType();
    responseTemp.response->values->values->value = values;
    
    response = responseTemp;
//    actionManager->addAction(action);
//    delete device;
    cout << "makeRemoteAction, guid: " << device->GUID << ", luid: " << device->LUID << ", cat: " << device->category << ", comm: " << command << endl;
    return 0;
}

int CSoapServer::getDevicesList(LONG64 category, struct ns1__getDevicesListResponse &_param_1){
    Blob null;
    SDeviceDescription inputDevice;
    inputDevice.category = static_cast<EDeviceCategory>(category);
    Blob b = deviceManager->invokeRemoteAction(inputDevice, ACTION_LIST, null);
    Devices devices = b[BLOB_DEVICES_LIST].get<Devices>();
    vector<ns1__SDeviceDescription*> devicesPointers;
//    for (int i = 0; i < 2; i++){
    for (auto device : devices){
        ns1__SDeviceDescription *dev = new ns1__SDeviceDescription();
        dev->category = static_cast<LONG64>(device.category);
        dev->GUID = device.guid;
        dev->LUID = device.luid;
        dev->name = device.name;
        devicesPointers.push_back(dev);
    }
    cout<<"category: "<<category<<endl;
    cout<<"devices cnt: "<<devicesPointers.size()<<endl;
    struct ns1__getDevicesListResponse str;
    str.result = new ns1__devicesList();
    str.result->item = devicesPointers;
    _param_1 = str;
//    actionManager->addAction(action);
//    delete device;
//    cout << "makeRemoteAction, guid: " << device->GUID << ", luid: " << device->LUID << ", cat: " << device->category << ", comm: " << command << endl;
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

