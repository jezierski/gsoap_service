/* 
 * File:   CDeviceManager.cpp
 * Author: jezierski
 * 
 * Created on 8 lipiec 2013, 19:17
 */

#include "CDeviceManager.h"

CDeviceManager::CDeviceManager() {
    log = CLog::getInstance();

}

//CDeviceManager::CDeviceManager(const CDeviceManager& orig) {
//}

CDeviceManager::~CDeviceManager() {
}

void CDeviceManager::addCategoryDevice(CDevice *device) {
    categoryDevices.push_back(device);
}

//void CDeviceManager::searchLogicalDevices(){
//    
//}

CDevice *CDeviceManager::getDevice(SDeviceDescription deviceDescription) {
    for (CDevice* catDevice : categoryDevices) {
        if (catDevice->getDeviceCategory() == deviceDescription.category) {
            //for (auto &logicalDevice : catDevice->getLogicalDevies()) {
            //   if (logicalDevice == deviceDescription)
            return catDevice;
            //}
        }

    }
    log->error("Device " + to_string(deviceDescription) + " not found");
    return NULL;
}

void CDeviceManager::invokeRemoteAction(SDeviceDescription device, Command command, Blob params) {
    if (device.category == EDeviceCategory::ALL) {
        for (CDevice* catDevice : categoryDevices) {
            catDevice->executeAction(device, command, params);
        }
    } else {
        CDevice *categoryDevice = getDevice(device);
        if (categoryDevice != NULL) {
            categoryDevice->executeAction(device, command, params);
        }
    }

}

