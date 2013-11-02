/* 
 * File:   CCanPWMActor.h
 * Author: jezierski
 *
 * Created on November 2, 2013, 3:10 PM
 */

#ifndef CCANPWMACTOR_H
#define	CCANPWMACTOR_H

#include "../homesys/CDevice.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CLog.h"
#include "CCanConstans.h"

#define CMD_SET_PWM             114
#define CMD_GET_PWM             115
#define CMD_PWM_UP              116
#define CMD_PWM_DOWN            117
#define CMD_SET_PWM_ALL         118
#define CMD_PWM_UP_ALL          119
#define CMD_PWM_DOWN_ALL        120
#define CMD_SET_PWM_ALL_THE_SAME    121

#define ACTION_SET_PWM             114
#define ACTION_GET_PWM             115
#define ACTION_PWM_UP              116
#define ACTION_PWM_DOWN            117
#define ACTION_SET_PWM_ALL         118
#define ACTION_PWM_UP_ALL          119
#define ACTION_PWM_DOWN_ALL        120
#define ACTION_SET_PWM_ALL_THE_SAME    121

using namespace std;


class CCanPWMActor : public CDevice{
public:
    CCanPWMActor();
//    CCanPWMActor(const CCanPWMActor& orig);
    virtual ~CCanPWMActor();
private:
    Blob setPWM(SDeviceDescription device, Blob params);
    Blob getPWM(SDeviceDescription device, Blob params);
    Blob increasePWM(SDeviceDescription device, Blob params);
    Blob decreasePWM(SDeviceDescription device, Blob params);
    Blob setAllPWM(SDeviceDescription device, Blob params);
    Blob setAllTheSamePWM(SDeviceDescription device, Blob params);
    Blob increaseAllPWM(SDeviceDescription device, Blob params);
    Blob decreaseAllPWM(SDeviceDescription device, Blob params);

    void initActionMap();


    EDeviceCategory category = EDeviceCategory::A_PWM_DRIVER;
    CLog *log;

};

#endif	/* CCANPWMACTOR_H */

