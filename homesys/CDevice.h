/* 
 * File:   CDevice.h
 * Author: Jezierski
 *
 * Created on 1 czerwiec 2013, 20:00
 */

#ifndef CDEVICE_H
#define	CDEVICE_H

#include <map>
#include "../can_devices/CCanConstans.h"
#include "../can232/CCan232.h"
#include "../tools/CCanBuffer.h"




class CDevice {
public:
    CDevice();
//    CDevice(const CDevice& orig);
    virtual ~CDevice();
    
    void setDeviceCategory(EDeviceCategory category);
    EDeviceCategory getDeviceCategory();
    
    void setCommunicationProtocol(CCan232 protocol);
    unsigned char getNewAddress();
    

//    void addNewDevice(unsigned char address);
    void resetAddresses();
    
private:
    map<unsigned char, string> devicesDescriptionList;
    EDeviceCategory category;
    CCan232 canbusProtocol;
};

#endif	/* CDEVICE_H */

