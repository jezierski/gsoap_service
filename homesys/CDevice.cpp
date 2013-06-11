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

void CDevice::setCommunicationProtocol(CCan232 *protocol) {
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

void CDevice::resetAddresses() {
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_RESET_ADDRESS);
    buffer.buildBuffer();
    canbusProtocol->sendCanFrame(buffer);
}

void CDevice::initAddress() {
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_INIT_ADDRESS);
    buffer.buildBuffer();
    canbusProtocol->sendCanFrame(buffer);
}

void CDevice::assignAddresses() {
    unsigned int TOUT = 1000; //@TODO move to DB
    CTimeOut tout;
    CCanBuffer buffer;
    unsigned int uid;
    unsigned char address;
    tout.SetMilliSec(TOUT);
    while (!tout.IsTimeOut()) {
        buffer = canbusProtocol->getCanFrame();
        if (CMD_REQ_ADDRESS == buffer.frameCommand()) {
            uid = buffer.getUID();

            cout << "uid: " << uid << endl;

            address = getNewAddress();
            cout << "new address: " << (int) address << endl;

            buffer.clear();
            buffer.insertCommand(CMD_SET_ADDRESS);
            buffer.insertId((unsigned char) category);
            buffer << (unsigned char) address;
            buffer << (unsigned char) (uid >> 24);
            buffer << (unsigned char) (uid >> 16);
            buffer << (unsigned char) (uid >> 8);
            buffer << (unsigned char) (uid >> 0);
            buffer.buildBuffer();
            canbusProtocol->sendCanFrame(buffer);
            tout.SetMilliSec(TOUT);
        }
        if (CMD_ACK == buffer.frameCommand()) {
            cout << "ACK from device CAT: " << (int) buffer[0] << ", ADR: " << (int) buffer[2] << endl;
            tout.SetMilliSec(TOUT);
        }
    }

}