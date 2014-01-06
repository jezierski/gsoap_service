/* 
 * File:   CDeviceManager.cpp
 * Author: jezierski
 * 
 * Created on 8 lipiec 2013, 19:17
 */

#include "CDeviceManager.h"

CDeviceManager::CDeviceManager() {
    log = CLog::getInstance();
    actionChain = new CActionsChain();
    loadActionsChain();

}

//CDeviceManager::CDeviceManager(const CDeviceManager& orig) {
//}

CDeviceManager::~CDeviceManager() {
}

void CDeviceManager::addCategoryDevice(CDevice *device) {
    categoryDevices.push_back(device);
}

void CDeviceManager::addBootDevice(CDevice *device) {
    bootDevice = device;
}

void CDeviceManager::uploadFirmware() {
    if (bootDevice != NULL) {
        pauseDeviceManager();
        bootDevice->uploadFirmware();
        resumeDeviceManager();
    }
}

void CDeviceManager::test() {
    CFirmwareLoader loader;
    CFirmwareBuffer firmware;
    string fname;

    if (bootDevice != NULL) {
        //        pauseDeviceManager();
        cout << "test, reset, exit, verify, init, read ???" << endl;
        string in;
        cin >> in;
        try {
            if (in == "test")
                bootDevice->test();
            if (in == "reset")
                bootDevice->resetDevice();
            if (in == "exit")
                bootDevice->exitBootMode();
            if (in == "init")
                bootDevice->initBootRead(0x800);
            if (in == "read")
                bootDevice->readProgramData();
            if (in == "verify") {


                loader.printFileList();
                log->put("Enter firmware file name to upload:");
                cin >> fname;

                firmware = loader.readFile(fname);

                bootDevice->verifyFirmware(firmware);

            }
        } catch (string e) {
            cout << "ERR: " << e << endl;
        }
        //        resumeDeviceManager();
    }
}

//void CDeviceManager::searchLogicalDevices(){
//    
//}

void CDeviceManager::loadActionsChain() {
    actionChain->loadActionsChain();
}

void CDeviceManager::initialize() {
    SDeviceDescription empty;
    Blob null;
    empty.category = EDeviceCategory::ALL;
    invokeRemoteAction(empty, ACTION_RESET_CATEGORY, null);
    invokeRemoteAction(empty, ACTION_SEARCH_DEVICES, null);
    invokeRemoteAction(empty, ACTION_RESET_ALL_STATUS, null);
}

CDevice *CDeviceManager::getDevice(SDeviceDescription deviceDescription) {
    for (CDevice* catDevice : categoryDevices) {
        if (catDevice->getDeviceCategory() == deviceDescription.category) {
            return catDevice;
        }

    }
    log->error("Device " + to_string(deviceDescription) + " not found");
    return new CDevice();
}

Blob CDeviceManager::invokeRemoteAction(SDeviceDescription device, Command command, Blob params) {
    lock_guard<mutex> lock(action);
    Blob returnVal;
    if (device.category == EDeviceCategory::ALL) {
        for (CDevice* catDevice : categoryDevices) {
            returnVal = catDevice->executeAction(device, command, params);
        }
    } else {
        SAction action = convertToSAction(device, command, params);
        CDevice *categoryDevice = getDevice(device);
        returnVal = categoryDevice->executeAction(action);
        while (actionChain->isChainExist(action)) {
            categoryDevice = getDevice(device);
            categoryDevice->executeAction(action);
        }
    }

    return returnVal;
}

SAction CDeviceManager::convertToSAction(SDeviceDescription device, Command command, Blob blob) {
    SAction action;
    action.device = device;
    action.command = command;
    action.params = blob;
    return action;

}

Blob CDeviceManager::invokeGlobalRemoteAction(Command command, Blob params) {
    SDeviceDescription device;
    Blob returnVal;
    device.category = EDeviceCategory::ALL;
    for (CDevice* catDevice : categoryDevices) {
        catDevice->executeAction(device, command, params);
    }

    return returnVal;
}

void CDeviceManager::runInThreadRemoteAction(SDeviceDescription device, Command command, Blob params) {
    while (1) {
        invokeRemoteAction(device, command, params);
        //        msleep(10);
    }
}

void CDeviceManager::runInThreadGlobalRemoteAction(Command command, Blob params) {

    while (1) {
        invokeGlobalRemoteAction(command, params);
        msleep(100);
        while (pause) {
            msleep(500);
        }
    }
}

void CDeviceManager::pauseDeviceManager() {
    pause = true;
}

void CDeviceManager::resumeDeviceManager() {
    pause = false;
}

list<CDevice*> CDeviceManager::getDevices() {
    return categoryDevices;
}
