/* 
 * File:   CActionManager.cpp
 * Author: jezierski
 * 
 * Created on September 24, 2013, 9:00 PM
 */

#include "CActionManager.h"

CActionManager::CActionManager() {
}

//CActionManager::CActionManager(const CActionManager& orig) {
//}

CActionManager::~CActionManager() {
}

void CActionManager::addOperation(SOperation operation){
    lock_guard<mutex> lock(operationLock);
    operationsList.push_back(operation);
}

void CActionManager::makeOperation(){
    lock_guard<mutex> lock(operationLock);
    SOperation operation = operationsList.front();
    operationsList.pop_front();
    deviceManager->invokeRemoteAction(operation.action.device, operation.action.command, operation.action.params);
}


void CActionManager::assignDeviceManager(CDeviceManager* deviceManager) {
    this->deviceManager = deviceManager;
}


void CActionManager::runActionManager(){
    while(1){
        if (operationsList.size()){
            makeOperation();
        }
        
        msleep(10);
    }
}