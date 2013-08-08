/* 
 * File:   CDevice.h
 * Author: Jezierski
 *
 * Created on 1 czerwiec 2013, 20:00
 */

#ifndef CDEVICE_H
#define	CDEVICE_H

#include <map>
#include <vector>

#include "../tools/CDevicesConfig.h"
#include "../can_devices/CCanConstans.h"
#include "../can232/CCan232.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CTimeOut.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "../tools/FastDelegate.h"
#include "../tools/Signal.h"


#define BLOB_ACTION_PARAMETER        "param"
#define BLOB_DEVICE_NAME             "name"

#define ACTION_RESET_CATEGORY           1
#define ACTION_SEARCH_DEVICES           2
#define ACTION_CHECK_AVAILABILITY       3
#define ACTION_LIST                     4
#define ACTION_RESET_ALL_STATUS         5
#define ACTION_READ_NEW_STATUS          6
#define ACTION_SET_NAME                 11
#define ACTION_PING                     12

#define GLOBAL_ACTION_LIMIT           10

using namespace Gallant;


class CDevice {
public:
    CDevice();
    //    CDevice(const CDevice& orig);
    virtual ~CDevice();
    Signal3<SDeviceDescription, Command, Params> sensorEvent;
    

    void setDeviceCategory(EDeviceCategory category);
    EDeviceCategory getDeviceCategory();

    void setCommunicationProtocol(CCan232 *protocol);

    Devices getLogicalDevies();

    void executeAction(SDeviceDescription, Command, Blob);
    void executeAction(SAction action);
    void executeGlobalAction(Command, Blob);

    template<typename T>
    void addAction(T *object, Command command, void(T::*function)(SDeviceDescription, Blob)) {
        Delegate delegateFunction;
        delegateFunction.bind(object, function);
        actionsMap[command] = delegateFunction;
    }

    typedef fastdelegate::FastDelegate2<SDeviceDescription, Blob> Delegate;
    map<Command, Delegate> actionsMap;





    void reset(SDeviceDescription dev, Blob params);
    void search(SDeviceDescription dev, Blob params);
    void check(SDeviceDescription dev, Blob params);
    void setName(SDeviceDescription dev, Blob params);
    void pingLogicalDevice(SDeviceDescription dev, Blob params);
    void list(SDeviceDescription dev, Blob params);
    void resetStatuses(SDeviceDescription dev, Blob params);
    void checkNewStatuses(SDeviceDescription dev, Blob params);

    CCan232 *getProtocol();
    unsigned char getAddress(SDeviceDescription device);

    

   


private:
    unsigned char getNewAddress();
    void removeAddress(unsigned char address);

    bool ping(SDeviceDescription);


    void resetAddresses();
    void findGUIDs();
//    void pollGUID();
//    void getGUIDs();
//    void sendPollACK(unsigned int guid);
    void assignAddress();

    void resetAllDevicesStatus();
    void checkNewDevicesStatus();
//    void requestNewDevicesStatus();
//    void getNewDevicesStatus();
    void sendACK(SDeviceDescription device);



    void listAddresses();
    void checkDevicesAvailability();

    void insertDevice(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address);
    void removeDevice(unsigned char address);
    void synchronizeDBdevices();
    void sortDevicesList(Devices &devices);
    unsigned char getDeviceGroupSize(Devices devicesList, unsigned int guid, EDeviceCategory category);
    void synchronizeDeviceName(SDeviceDescription description, string name, EDeviceCategory category, Devices &devicesList);
    void setDeviceName(SDeviceDescription description, string name);
    string getDeviceName(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList);
    unsigned char getDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList);
    SDeviceDescription getDeviceWithAddress(unsigned char address);
    void setDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address, Devices &devicesList);
    
    
    void initActionMap();

    bool isSensorDevice() {
        return (static_cast<unsigned char> (category) >= 100) && (static_cast<unsigned char> (category) < 200);
    }

    bool isActorDevice() {
        return (static_cast<unsigned char> (category) < 100);
    }


    Devices devicesDescriptionList;
    EDeviceCategory category;
    CCan232 *canbusProtocol;
    CLog *log;
    map<unsigned int, unsigned char> GUIDs;
    CDevicesConfig *devicesDB;
};

#endif	/* CDEVICE_H */

