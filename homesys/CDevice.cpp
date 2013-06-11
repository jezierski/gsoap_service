/* 
 * File:   CDevice.cpp
 * Author: Jezierski
 * 
 * Created on 1 czerwiec 2013, 20:00
 */

#include "CDevice.h"

CDevice::CDevice() {
}

//CDevice::CDevice(const CDevice& orig) {
//}

CDevice::~CDevice() {
}

void CDevice::setDeviceCategory(EDeviceCategory category) {
    this->category = category;
}

EDeviceCategory CDevice::getDeviceCategory() {
    return category;
}

void CDevice::setCommunicationProtocol(CCan232 protocol) {
    canbusProtocol = protocol;
}

unsigned char CDevice::getNewAddress() {
    unsigned char address = 0;
    std::pair < std::map<unsigned char, string>::iterator, bool> ret;
    do {
        address++;
        ret = devicesDescriptionList.insert(std::pair<unsigned char, string>(address, ""));
    } while (ret.second == false);
    return address;
}

void CDevice::resetAddresses(){
    CCanBuffer buffer;
    buffer.insertId((unsigned char)category);
    buffer.insertCommand(CMD_RESET_ADDRESS);
    canbusProtocol->sendCanFrame(buffer);
}