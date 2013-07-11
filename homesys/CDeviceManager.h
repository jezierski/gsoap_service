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
    CDevice *getLogicalDevice(SDeviceDescription deviceDescription);
    //void resetDeviceAddresses();
    //void assignAddresses();
    

    void invokeRemoteFunction(SDeviceDescription, Command, Params);
  
 
   

private:
    list<CDevice*>categoryDevices;
    CLog *log;
};

#endif	/* CDEVICEMANAGER_H */

