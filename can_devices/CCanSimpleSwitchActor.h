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


#define CMD_ACTION_TEST 1
#define CMD_SET_SWITCH 2



using namespace std;

class CCanSimpleSwitchActor : public CDevice {
public:
    CCanSimpleSwitchActor();
//    CCanSimpleSwitch(const CCanSimpleSwitch& orig);
    virtual ~CCanSimpleSwitchActor();
    
//    typedef void (CCanSimpleSwitchActor::*action)(SDeviceDescription, Params);
//    map<int, action> actionMap;
//    void executeFunction(SDeviceDescription, Command, Params);
  
private:
    void actionTest(SDeviceDescription device, Params params);
    void setSwitch(SDeviceDescription device, Params params);
    void initActionMap();
    
    CLog *log;
};

#endif	/* CCANSIMPLESWITCH_H */
