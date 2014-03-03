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
#include "../tools/CFirmwareLoader.h"
#include "../tools/CFirmwareBuffer.h"



#define ACTION_RESET_CATEGORY           1
#define ACTION_SEARCH_DEVICES           2
#define ACTION_CHECK_AVAILABILITY       3
#define ACTION_LIST                     4
#define ACTION_RESET_ALL_STATUS         5
#define ACTION_READ_NEW_STATUS          6
#define ACTION_SET_NAME                 11
#define ACTION_PING                     12
#define ACTION_BOOT                     13

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

    Blob executeAction(SDeviceDescription, Command, Blob);
    Blob executeAction(SAction action);
    Blob executeGlobalAction(Command, Blob);

    template<typename T>
    void addAction(T *object, Command command, Blob(T::*function)(SDeviceDescription, Blob)) {
        Delegate delegateFunction;
        delegateFunction.bind(object, function);
        actionsMap[command] = delegateFunction;
    }

    typedef fastdelegate::FastDelegate2<SDeviceDescription, Blob, Blob> Delegate;
    map<Command, Delegate> actionsMap;





    Blob reset(SDeviceDescription dev, Blob params);
    Blob search(SDeviceDescription dev, Blob params);
    Blob check(SDeviceDescription dev, Blob params);
    Blob setName(SDeviceDescription dev, Blob params);
    Blob pingLogicalDevice(SDeviceDescription dev, Blob params);
    Blob bootDevice(SDeviceDescription dev, Blob params);
    Blob list(SDeviceDescription dev, Blob params);
    Blob resetStatuses(SDeviceDescription dev, Blob params);
    Blob checkNewStatuses(SDeviceDescription dev, Blob params);

    CCan232 *getProtocol();
    unsigned char getAddress(SDeviceDescription device);

    vector<string> getFirmwareFilesList();
    void uploadFirmware(string fileName);


    
    
private:

 
     /*firmware upload methods*/
    void resetDevice();
    bool checkReady();
    void getDummyFrames();
    void clearFlash();
    void exitBootMode();
    void initBootWrite(unsigned int address);
    void initBootRead(unsigned int address);
    void initSelfCRC();
    unsigned int getSelfCRC();
    void writeProgramData(CBuffer data);
    CCanBuffer readProgramData();
     int readGUID();
     void initWriteGUID();
     void writeGUID();
     
     void setGuidIfNeed();
    void uploadExFirmware(CFirmwareBuffer &buffer);
    unsigned int uploadFirmware(CFirmwareBuffer &buffer);
    void verifyFirmware(unsigned int crc);
    void calcCRC(unsigned int &crc, CFirmwareBuffer buf);

    unsigned char getNewAddress();
    void removeAddress(unsigned char address);

    bool ping(SDeviceDescription);


    bool resetAddresses();
    void findGUIDs();
    //    void pollGUID();
    //    void getGUIDs();
    //    void sendPollACK(unsigned int guid);
    void assignAddress();

    bool resetAllDevicesStatus();
    void checkNewDevicesStatus();
    //    void requestNewDevicesStatus();
    //    void getNewDevicesStatus();
    void sendACK(SDeviceDescription device);



    Blob listAddresses();
    Blob checkDevicesAvailability();

    void insertDevice(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address);
    void removeDevice(unsigned char address);
    void synchronizeDBdevices();
    void sortDevicesList(Devices &devices);
    unsigned char getDeviceGroupSize(Devices devicesList, unsigned int guid, EDeviceCategory category);
    Blob synchronizeDeviceName(SDeviceDescription description, string name, EDeviceCategory category, Devices &devicesList);
    Blob setDeviceName(SDeviceDescription description, string name);
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
    EDeviceCategory category = EDeviceCategory::ALL;
    CCan232 *canbusProtocol;
    CLog *log;
    map<unsigned int, unsigned char> GUIDs;
    CDevicesConfig *devicesDB;
};

#endif	/* CDEVICE_H */

