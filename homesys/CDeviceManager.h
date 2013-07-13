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

using namespace std;



class CDeviceManager {
public:
    CDeviceManager();
    //    CDeviceManager(const CDeviceManager& orig);
    virtual ~CDeviceManager();

    void addCategoryDevice(CDevice *device);
    //void searchLogicalDevices();
    
//    void resetDeviceAddresses();
    //void assignAddresses();
    

    void invokeRemoteAction(SDeviceDescription, Command, Blob);
  
 
   

private:
    CDevice *getDevice(SDeviceDescription deviceDescription);
    list<CDevice*>categoryDevices;
    CLog *log;
};

#endif	/* CDEVICEMANAGER_H */

