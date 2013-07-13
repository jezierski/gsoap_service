/* 
 * File:   CDevice.h
 * Author: Jezierski
 *
 * Created on 1 czerwiec 2013, 20:00
 */

#ifndef CDEVICE_H
#define	CDEVICE_H

#include <map>
#include "../tools/CDevicesConfig.h"
#include "../can_devices/CCanConstans.h"
#include "../can232/CCan232.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CTimeOut.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "../tools/FastDelegate.h"

class CDevice {
public:
    CDevice();
    //    CDevice(const CDevice& orig);
    virtual ~CDevice();

    void setDeviceCategory(EDeviceCategory category);
    EDeviceCategory getDeviceCategory();

    void setCommunicationProtocol(CCan232 *protocol);
    unsigned char getNewAddress();
    void removeAddress(unsigned char address);

    bool ping(unsigned char address);


    //    void addNewDevice(unsigned char address);
    void resetAddresses();
    void pollGUID();
    void getGUIDs();
    void sendPollACK(unsigned int guid);
    void assignAddress();
    void setDeviceName(unsigned char address, string name, EDeviceCategory category);



    void listAddresses(); //@TODO remove it
    void checkDevicesAvailability(); //@TODO move to private
    Devices getLogicalDevies();

    void executeFunction(SDeviceDescription, Command, Params);
    
//    template<typename T>
//    void addFunction(T *object, Command command, void(T::*function)(SDeviceDescription, Command , Params)){
//        typedef void (T::*function)(SDeviceDescription, Command , Params);
//        map<Command, function> dupa;
//        dupa[command] = (T::*function)(SDeviceDescription, Command , Params);
//    }
//    typedef void (CDevice::*action)(SDeviceDescription, Params);
//    map<Command, action> actionMap;
    template<typename T>
    void addFunction(T *object, Command command, void(T::*function)(SDeviceDescription, Params)){
        Delegate delegateFunction;
        delegateFunction.bind(object, function);
        functionsMap[command] = delegateFunction;
    }
    
    typedef fastdelegate::FastDelegate2<SDeviceDescription, Params> Delegate;
    map<Command, Delegate> functionsMap;
    /////////////////////////////////////////////////
    
    
    void addCategoryDevice(SDeviceDescription dev){//@TODO remove it
        devicesDescriptionList.push_back(dev);
    }
    
private:
    void insertDevice(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address);
    void removeDevice(unsigned char address);
    void synchronizeDBdevices();
    void sortDevicesList(Devices &devices);
    unsigned char getDeviceGroupSize(Devices devicesList, unsigned int guid, EDeviceCategory category);
    void setDeviceName(unsigned int guid, unsigned char luid, string name, EDeviceCategory category, Devices &devicesList);
    string getDeviceName(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList);
    unsigned char getDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList);
    void setDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address, Devices &devicesList);

    Devices devicesDescriptionList;
    EDeviceCategory category;
    CCan232 *canbusProtocol;
    CLog *log;
    map<unsigned int, unsigned char> GUIDs;
    CDevicesConfig *devicesDB;
};

#endif	/* CDEVICE_H */
