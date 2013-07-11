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

CDevice *CDeviceManager::getLogicalDevice(SDeviceDescription deviceDescription) {
    for (CDevice* catDevice : categoryDevices) {
        if (catDevice->getDeviceCategory() == deviceDescription.category) {
            for (auto &logicalDevice : catDevice->getLogicalDevies()) {
                if (logicalDevice == deviceDescription)
                    return catDevice;
            }
        }

    }
    log->error("No device found " + to_string(deviceDescription));
    return NULL;
}

void CDeviceManager::invokeRemoteFunction(SDeviceDescription device, Command command, Params params) {
    CDevice *categoryDevice = getLogicalDevice (device);
    if (categoryDevice != NULL){
        categoryDevice->executeFunction(device, command, params);
    }
    
}
