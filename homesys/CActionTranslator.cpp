/* 
 * File:   CActionTranslator.cpp
 * Author: jezierski
 * 
 * Created on August 4, 2013, 9:36 AM
 */

#include <list>
#include <map>
#include <algorithm>

#include "CActionTranslator.h"

CActionTranslator::CActionTranslator() {
    log = CLog::getInstance();
    operations = new COperation();

}

//CActionTranslator::CActionTranslator(const CActionTranslator& orig) {
//}

CActionTranslator::~CActionTranslator() {
}

void CActionTranslator::loadOperations() {
    operations->loadOperations();
    timer->resetTimerSet();
    setTimer(operations);
}

void CActionTranslator::setTimer(COperation *operations) {
    for (SOperation operation : operations->getOperations()) {
        for (STimeCondition timeCond : operation.timeConditions) {
            timer->addTimerSet(timeCond.time);
        }
    }
}

void CActionTranslator::updateDeviceState(SDeviceDescription device, Command command, Params params) {
    lock_guard<mutex> lock(deviceMutex);
    deviceState[device][command] = params;
    DeviceState state;
    state[device][command] = params;
    deviceStateStack.push_back(state);
    log->info("New device state: " + to_string(device) + ", COM: " + to_string((int)command) + ", PARAMS: " + to_string(params));


    //@TODO remove below
    //    cout << "=====>>>>> UPDATE DEVICE STATE" << endl;
    //    log->put("Device " + to_string(device) + ", COM: " + to_string((int) command) + ", PAR NMB: " + to_string(params.size()));
    //    for (auto &cos : deviceState) {
    //        log->put("Device");
    //        log->put(to_string((SDeviceDescription) cos.first));
    //        log->put("Params:");
    //        for (auto &param : cos.second) {
    //            log->put("param: " + to_string((int) param.first));
    //            for (auto p : param.second) {
    //                log->put(to_string((int) p));
    //            }
    //        }
    //    }
    ///////////////////

}

void CActionTranslator::updateTimerStack(long long timer) {
    lock_guard<mutex> lock(timerMutex);
    timerStack.push_back(timer);
}

bool CActionTranslator::deviceCondition(SOperation &operation) {
    //@TODO remove below
    //    cout << "OPERATION" << endl;
    //    for (SDeviceCondition con : operation.deviceConditions) {
    //        cout << "===>DEVICE CONDITIONS:" << endl;
    //        cout << "param: " << (int) (con.command) << endl;
    //        cout << "condi: " << (int) (con.condition) << endl;
    //        cout << "guid : " << (int) (con.device.guid) << endl;
    //        cout << "luid : " << (int) (con.device.luid) << endl;
    //        cout << "categ: " << (int) (con.device.category) << endl;
    //        for (int i = 0; i < con.params.size(); i++) {
    //            cout << "param[" << i << "]: " << (int) (con.params[i]) << endl;
    //        }
    //    }
    //    cout << "checDeviceCONDITION" << endl;
    //////////////////

    for (SDeviceCondition condition : operation.deviceConditions) {
        if (not compareSDStoSDC(condition))
            return false;
    }
    return true;
}

bool CActionTranslator::compareSDStoSDC(SDeviceCondition condition) {
    lock_guard<mutex> lock(deviceMutex);
    //    cout << "CONDITION from XML: " << endl;
    //    cout << "guid: " << condition.device.guid << " luid: " << (int) condition.device.luid << ", command: " << (int) condition.command << ", comp: " << (int) condition.condition << endl;

    return compareParams(condition.condition, deviceState[condition.device][condition.command], condition.params);
}

bool CActionTranslator::compareTime(STimeCondition condition) {
    long long time = getCurrentDayTime();
    switch (condition.condition) {
        case ECondition::Equal:
            return time == condition.time;
            break;
        case ECondition::Less:
            return time < condition.time;
            break;
        case ECondition::More:
            return time > condition.time;
            break;
        case ECondition::LessOrEqual:
            return time <= condition.time;
            break;
        case ECondition::MoreOrEqual:
            return time >= condition.time;
            break;
    }
    return false;
}

bool CActionTranslator::compareParams(ECondition condition, Params params1, Params params2) {
    //    cout << "device params size: " << params1.size() << ", xml params size: " << params2.size() << endl;
    if ((params1.size() != params2.size()) || params1.size() == 0)
        return false;

    //    cout << "device param[0]: " << (int) params1[0] << ", xml param[0]: " << (int) params2[0] << endl;
    bool result = true;
    switch (condition) {
        case ECondition::Equal:
            //            cout << "check EQUAL" << endl;
            for (size_t i = 0; (i < params1.size()) && result; i++) {
                result = result && (params1[i] == params2[i]);
            }
            break;
        case ECondition::Less:
            //            cout << "check LESS" << endl;
            result = (params1[0] < params2[0]);
            break;
        case ECondition::More:
            //            cout << "check MORE" << endl;
            result = (params1[0] > params2[0]);
            break;
        case ECondition::LessOrEqual:
            //            cout << "check LESS or EQUAL" << endl;
            result = (params1[0] <= params2[0]);
            break;
        case ECondition::MoreOrEqual:
            //            cout << "check MORE or EQUAL" << endl;
            result = (params1[0] >= params2[0]);
            break;
    }
    //    cout << "result: " << (bool)result << endl;
    return result;
}

bool CActionTranslator::timeCondition(SOperation &operation) {
    for (STimeCondition condition : operation.timeConditions) {
        if (not compareTime(condition))
            return false;
    }
    return true;
}

void CActionTranslator::makeAction(SOperation &operation) {
    //    cout << ">>>>>>>>> MAKE ACTION <<<<<<<<<<<<<<<[" << endl;
    deviceManager->invokeRemoteAction(operation.action.device, operation.action.command, operation.action.params);

}

DeviceState CActionTranslator::popDeviceState() {
    lock_guard<mutex> lock1(deviceMutex);
    DeviceState dev = deviceStateStack.front();
    ;
    deviceStateStack.pop_front();
    return dev;
}

long long CActionTranslator::popTimerSet() {
    lock_guard<mutex> lock2(timerMutex);
    long long timerSet = timerStack.front();
    timerStack.pop_front();
    return timerSet;

}

void CActionTranslator::translateActions() {

    while (1) {
        DeviceState deviceState;
//        long long timerSet = 0;
        if (deviceStateStack.size()) {
            //            cout<<"\n\n\n#########  STACK SIZE: "<<deviceStateStack.size()<<endl;
            deviceState = popDeviceState();
            //            DeviceState::iterator it = deviceState.begin();
            //            cout<<"POP dev addr: "<<(int)it->first.address<<endl;
            //            cout<<"POP dev cat: "<<(int)it->first.category<<endl;
            //            cout<<"POP dev guid: "<<(int)it->first.guid<<endl;
            //            cout<<"POP dev luid: "<<(int)it->first.luid<<endl;
            //            DeviceParams::iterator iit = deviceState[it->first].begin();
            //            cout<<"POP dev comm: "<<(int)iit->first<<endl;
            //            
            //            cout << "\n\n======>>>>>> translate Actions LOOP" << endl;
            
            for (SOperation operation : operations->getOperations()) {
                if (isOperationForDeviceCondition(operation, deviceState)) {
                    if (deviceCondition(operation) && timeCondition(operation)) {
                        makeAction(operation);
                    }
                }
            }
        }
        if (timerStack.size()) {
            popTimerSet();

            for (SOperation operation : operations->getOperations()) {
                if (isOperationForTimer(operation)) {
                    if (deviceCondition(operation) && timeCondition(operation)) {
                        makeAction(operation);
                    }
                }
            }
        }
        msleep(10);
    }
}

bool CActionTranslator::isOperationForDeviceCondition(SOperation &operation, DeviceState deviceState) {

    for (SDeviceCondition con : operation.deviceConditions) {
        if (deviceState.find(con.device) != deviceState.end()) {
            //            cout << "found operation included SDD" << endl;
            if (deviceState[con.device].find(con.command) != deviceState[con.device].end()) {
                //                cout << "found operation with device command" << endl;
                return true;
            }
        }
    }
    return false;
}

bool CActionTranslator::isOperationForTimer(SOperation &operation) {
    lock_guard<mutex> lock(timerMutex);
    return (operation.timeConditions.size() > 0);
}

void CActionTranslator::assignDeviceManager(CDeviceManager* deviceManager) {
    this->deviceManager = deviceManager;
}

void CActionTranslator::assignTimer(CTimer* timer) {
    this->timer = timer;
}