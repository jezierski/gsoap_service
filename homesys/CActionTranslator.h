/* 
 * File:   CActionTranslator.h
 * Author: jezierski
 *
 * Created on August 4, 2013, 9:36 AM
 */

#ifndef CACTIONTRANSLATOR_H
#define	CACTIONTRANSLATOR_H

#include <map>
#include <list>
#include <mutex>
#include "COperation.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "../tools/CTools.h"
#include "CDeviceManager.h"
#include "CTimer.h"

using namespace std;
class CActionTranslator {
public:
    CActionTranslator();
//    CActionTranslator(const CActionTranslator& orig);
    virtual ~CActionTranslator();
    
    void updateDeviceState(SDeviceDescription, Command, Params);
    void updateTimerStack(long long timer);
    
    void translateActions();
    
    void assignDeviceManager(CDeviceManager *deviceManager);
    void assignTimer(CTimer *timer);
    
    void loadOperations();
    
private:
    
    bool deviceCondition(SOperation &operation);
    bool timeCondition(SOperation &operation);
    void makeAction(SOperation &operation);
    
    bool compareSDStoSDC(SDeviceCondition condition);
    bool compareTime(STimeCondition condition);
    
    bool isOperationForDeviceCondition(SOperation &operation, DeviceState deviceState);
    bool isOperationForTimer(SOperation &operation);
    
    bool compareParams(ECondition condition, Params params1, Params params2);
    
    void setTimer(COperation *operations);
    
    DeviceState popDeviceState();
    long long popTimerSet();
    
    DeviceState  deviceState;
    list<DeviceState> deviceStateStack;
    list<long long> timerStack;
    mutex deviceMutex;
    mutex timerMutex;
    CLog *log;
    COperation *operations;
    CDeviceManager *deviceManager;
    CTimer *timer;
};

#endif	/* CACTIONTRANSLATOR_H */

