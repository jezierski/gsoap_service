/* 
 * File:   CDeviceManager.h
 * Author: jezierski
 *
 * Created on 8 lipiec 2013, 19:17
 */

#ifndef CDEVICEMANAGER_H
#define	CDEVICEMANAGER_H

#include <map>
#include <list>
#include "CDevice.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "CActionsChain.h"
#include <mutex>

using namespace std;



class CDeviceManager {
public:
    CDeviceManager();
    //    CDeviceManager(const CDeviceManager& orig);
    virtual ~CDeviceManager();

    void addCategoryDevice(CDevice *device);
    void addBootDevice(CDevice *device);

    Blob invokeRemoteAction(SDeviceDescription, Command, Blob);
    Blob invokeGlobalRemoteAction(Command, Blob);
    void runInThreadRemoteAction(SDeviceDescription device, Command command, Blob params);
    void runInThreadGlobalRemoteAction(Command command, Blob params);
 
    void initialize();
    
    void loadActionsChain();
   
    list<CDevice*> getDevices();
    
    void uploadFirmware();
    
    

private:
    void pauseDeviceManager();
    void resumeDeviceManager();
    
    SAction convertToSAction(SDeviceDescription device, Command command, Blob blob);
    CDevice *getDevice(SDeviceDescription deviceDescription);
    list<CDevice*>categoryDevices;
    CDevice *bootDevice;
    CActionsChain *actionChain;
    CLog *log;
    mutex action;
    bool active = true;
};

#endif	/* CDEVICEMANAGER_H */

