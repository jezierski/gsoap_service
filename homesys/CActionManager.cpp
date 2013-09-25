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

void CActionManager::addAction(SAction action) {
    lock_guard<mutex> lock(actionLock);
    actionList.push_back(action);
}

void CActionManager::makeAction() {
    lock_guard<mutex> lock(actionLock);
    SAction action = actionList.front();
    deviceManager->invokeRemoteAction(action.device, action.command, action.params);
    actionList.pop_front();
}

void CActionManager::assignDeviceManager(CDeviceManager* deviceManager) {
    this->deviceManager = deviceManager;
}

void CActionManager::runActionManager() {
    while (1) {
        if (actionList.size()) {
            makeAction();
        }

        msleep(10);
    }
}