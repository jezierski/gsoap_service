/* 
 * File:   CCanSimpleSwitch.h
 * Author: jezierski
 *
 * Created on 10 czerwiec 2013, 20:55
 */

#ifndef CCANSIMPLESWITCHACTOR_H
#define	CCANSIMPLESWITCHACTOR_H

#include "../homesys/CDevice.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CLog.h"
#include "CCanConstans.h"

#define CATEGORY        EDeviceCategory::A_SIMPLE_SWITCH

#define ACTION_SET_OUTPUT       10


using namespace std;

class CCanSimpleSwitchActor : public CDevice {
public:
    CCanSimpleSwitchActor();
//    CCanSimpleSwitch(const CCanSimpleSwitch& orig);
    virtual ~CCanSimpleSwitchActor();
    
//    typedef void (CCanSimpleSwitchActor::*action)(SDeviceDescription, Params);
//    map<int, action> actionMap;
//    void executeAction(SDeviceDescription, Command, Params);
  
private:
    void setOutput(SDeviceDescription device, Blob params);
    void initActionMap();
    
    
    
    CLog *log;
};

#endif	/* CCANSIMPLESWITCH_H */

