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

string CSoapServer::readFile(string filename) {

    string fileContent;
    string text;
    ifstream myfile;
    myfile.open(filename);

    if (myfile.is_open()) {
        while (!myfile.eof()) {
            fileContent = "";
            myfile >> fileContent;

            text += fileContent + " ";
        }
        myfile.close();
    } else
        throw string("Unable to open file " + filename);

    return text;
}

int CSoapServer::getXML(string id, string &result) {
    string fileName = "";

    if (!id.compare("operations")) {
        fileName = "operations.xml";
    }

    if (!id.compare("chains")) {
        fileName = "actions_chain.xml";
    }

    if (!id.compare("descriptions")) {
        fileName = "device_descriptions.xml";
    }

    if (fileName.length()) {
        fileName = "../xml/" + fileName;
        result = readFile(fileName);
    } else {

        result = fileName;
    }

    return SOAP_OK;
}

int CSoapServer::saveXML(std::string id, std::string body, std::string &result) {
    string fileName = "";

    if (!id.compare("operations")) {
        fileName = "operations.xml";
    }

    if (!id.compare("chains")) {
        fileName = "actions_chain.xml";
    }

    if (!id.compare("descriptions")) {
        fileName = "device_descriptions.xml";
    }

    if (fileName.length()) {
        fileName = "../xml/" + fileName;
        fstream f(fileName, ios::in);
        if (f) {
            f.close();
            f.open(fileName, ios::out | ios::trunc);
            f << body;
            f.close();
            result = "OK";
            if (!id.compare("operations")) {
                operationLoad();
            } else if (!id.compare("chains")) {
                deviceManager->loadActionsChain();
            }
        } else {
            result = "No file " + fileName + " found";
        }

    } else {
        result = "No file ID " + id + " found";
    }

    return SOAP_OK;
}

int CSoapServer::switchPort(string pinNo, string & result) {
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

int CSoapServer::setDeviceName(ns1__SDeviceDescription *device, std::string name, std::string &response) {
    SDeviceDescription s;
    s.category = static_cast<EDeviceCategory> (device->category);

    s.guid = device->GUID;
    s.luid = device->LUID;
    Blob b;
    b[BLOB_DEVICE_NAME].put<string>(name);
    Blob resp = deviceManager->invokeRemoteAction(s, ACTION_SET_NAME, b);


    response = resp[BLOB_TXT_RESPONSE_RESULT].get <string> ();
    return SOAP_OK;
}

int CSoapServer::searchNewDevices(LONG64 category, struct ns1__searchNewDevicesResponse &_param_1) {
    
    SDeviceDescription empty;
    Blob null;
    empty.category = static_cast<EDeviceCategory>(category);
    deviceManager->invokeRemoteAction(empty, ACTION_RESET_CATEGORY, null);
    deviceManager->invokeRemoteAction(empty, ACTION_SEARCH_DEVICES, null);
    deviceManager->invokeRemoteAction(empty, ACTION_RESET_ALL_STATUS, null);
    return SOAP_OK;
}

int CSoapServer::makeRemoteAction(ns1__SDeviceDescription *device, LONG64 command, LONG64 params, struct ns1__makeRemoteActionResponse & response) {
    SAction action;
    action.command = command;
    action.params = converter->use(device->category, command, params);
    action.device.category = static_cast<EDeviceCategory> (device->category);
    action.device.guid = device->GUID;
    action.device.luid = device->LUID;
    Blob b = deviceManager->invokeRemoteAction(action.device, action.command, action.params);
    vector<LONG64>values = b[BLOB_RESPONSE_INT_VALUES].get < vector < LONG64 >> ();

    
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
    cout << "makeRemoteAction, guid: " << device->GUID << ", luid: " << device->LUID << ", cat: " << device->category << ", comm: " << command << ", params[" << params << "]: ";
    for (int i = 8; i > 0; i--) {
        cout << (int) ((params >> ((i - 1) * 8)) & 0xff) << " ";
    }

    cout << endl;
    return SOAP_OK;
}

int CSoapServer::getDevicesList(LONG64 category, struct ns1__getDevicesListResponse & _param_1) {
    Blob null;
    SDeviceDescription inputDevice;
    inputDevice.category = static_cast<EDeviceCategory> (category);
    Blob b = deviceManager->invokeRemoteAction(inputDevice, ACTION_LIST, null);
    Devices devices = b[BLOB_DEVICES_LIST].get<Devices>();
    vector<ns1__SDeviceDescription*> devicesPointers;
    //    for (int i = 0; i < 2; i++){
    for (auto device : devices) {
        ns1__SDeviceDescription *dev = new ns1__SDeviceDescription();
        dev->category = static_cast<LONG64> (device.category);
        dev->GUID = device.guid;
        dev->LUID = device.luid;
        dev->name = device.name;
        devicesPointers.push_back(dev);
    }
    cout << "category: " << category << endl;
    cout << "devices cnt: " << devicesPointers.size() << endl;
    struct ns1__getDevicesListResponse str;
    str.result = new ns1__devicesList();
    str.result->item = devicesPointers;
    _param_1 = str;
    //    actionManager->addAction(action);
    //    delete device;
    //    cout << "makeRemoteAction, guid: " << device->GUID << ", luid: " << device->LUID << ", cat: " << device->category << ", comm: " << command << endl;

    return SOAP_OK;
}


int CSoapServer::getFilesList(struct ns1__getFilesListResponse & _param_1) {
    vector<string > fileNames = deviceManager->getFirmwareFilesList();
    struct ns1__getFilesListResponse response;
    response.result = new ns1__filesList();
    response.result->fileName = fileNames;
    
    _param_1 = response;
    
    return SOAP_OK;
}

int CSoapServer::uploadFirmware(std::string fileName, struct ns1__uploadFirmwareResponse &_param_5){
    deviceManager->uploadFirmware(fileName);
    
    return SOAP_OK;
}

void CSoapServer::start() {
    int error;
    while (1) {
        error = run(1234);
        if (error != SOAP_OK)
            log->error("SOAP server error code: " + to_string(error) + ", trying to restart in a 3 sec...");
        sleep(3);
    }
}

