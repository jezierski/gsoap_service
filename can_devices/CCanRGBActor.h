/* 
 * File:   CCanRGBActor.h
 * Author: jezierski
 *
 * Created on September 11, 2013, 6:16 PM
 */

#ifndef CCANRGBACTOR_H
#define	CCANRGBACTOR_H


#include "../homesys/CDevice.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CLog.h"
#include "CCanConstans.h"



#define ACTION_SET_CHANNEL_RED     102
#define ACTION_SET_CHANNEL_GREEN   103
#define ACTION_SET_CHANNEL_BLUE    104
#define ACTION_SET_CHANNEL_ALL     105
#define ACTION_SET_MODE       106
#define ACTION_SET_SPEED       107
#define ACTION_GET_CHANNEL_RED     108
#define ACTION_GET_CHANNEL_GREEN   109
#define ACTION_GET_CHANNEL_BLUE    110
#define ACTION_GET_CHANNEL_ALL     111
#define ACTION_GET_MODE            112
#define ACTION_GET_SPEED           113


#define CMD_SET_CHANNEL_RED     102
#define CMD_SET_CHANNEL_GREEN   103
#define CMD_SET_CHANNEL_BLUE    104
#define CMD_SET_CHANNEL_ALL     105
#define CMD_SET_MODE            106
#define CMD_SET_SPEED           107
#define CMD_GET_CHANNEL_RED     108
#define CMD_GET_CHANNEL_GREEN   109
#define CMD_GET_CHANNEL_BLUE    110
#define CMD_GET_CHANNEL_ALL     111
#define CMD_GET_MODE            112
#define CMD_GET_SPEED           113

using namespace std;

class CCanRGBActor : public CDevice {
public:
    CCanRGBActor();
    //    CCanRGBActor(const CCanRGBActor& orig);
    virtual ~CCanRGBActor();
private:
    Blob setMode(SDeviceDescription device, Blob params);
    Blob setSpeed(SDeviceDescription device, Blob params);
    Blob setRed(SDeviceDescription device, Blob params);
    Blob setGreen(SDeviceDescription device, Blob params);
    Blob setBlue(SDeviceDescription device, Blob params);
    Blob setRGB(SDeviceDescription device, Blob params);
    
    Blob getSpeed(SDeviceDescription device, Blob params);
    void initActionMap();


    EDeviceCategory category = EDeviceCategory::A_RGB_DRIVER;
    CLog *log;
};

#endif	/* CCANRGBACTOR_H */

