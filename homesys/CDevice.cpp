/* 
 * File:   CDevice.cpp
 * Author: Jezierski
 * 
 * Created on 1 czerwiec 2013, 20:00
 */

#include "CDevice.h"

CDevice::CDevice() {
    devicesDB = CDevicesConfig::getInstance();
    log = CLog::getInstance();

    initActionMap();
}

//CDevice::CDevice(const CDevice& orig) {
//}

CDevice::~CDevice() {
}

void CDevice::initActionMap() {
    addAction(this, ACTION_RESET_CATEGORY, &CDevice::reset);
    addAction(this, ACTION_SEARCH_DEVICES, &CDevice::search);
    addAction(this, ACTION_CHECK_AVAILABILITY, &CDevice::check);
    addAction(this, ACTION_SET_NAME, &CDevice::setName);
    addAction(this, ACTION_PING, &CDevice::pingLogicalDevice);
    addAction(this, ACTION_LIST, &CDevice::list);
    addAction(this, ACTION_RESET_ALL_STATUS, &CDevice::resetStatuses);
    addAction(this, ACTION_READ_NEW_STATUS, &CDevice::checkNewStatuses);
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
    bool ok;
    do {
        ok = true;
        address++;
        for (auto &device : devicesDescriptionList) {
            if (device.address == address) {
                ok = false;
                break;
            }
        }
    } while (address < 255 && not ok);
    return address;
}

void CDevice::resetAddresses() {
    try {
        devicesDB->clearAddresses();
        devicesDescriptionList.clear();
        CCanBuffer buffer;
        buffer.insertId((unsigned char) category);
        buffer.insertCommand(CMD_RESET_ADDRESS);
        buffer.buildBuffer();
        canbusProtocol->send(buffer);
    } catch (string e) {
        log->error("Cannot reset addresses: " + e);
    }
}

void CDevice::findGUIDs() {
    CCanBuffer buffer;
    GUIDs.clear();
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_POLL_GUID);
    buffer.buildBuffer();
    CanBuffers guids;
    guids = canbusProtocol->broadcastRequest<unsigned int>(buffer, &CCanBuffer::getGUID);
    for (CCanBuffer buf : guids) {
        GUIDs[buf.getGUID()] = buf.getNmbDevices();
        cout << "> received new GUID: " << hex << (int) buf.getGUID() << dec << ", nmb devs: " << (int) buf.getNmbDevices() << endl;//@TODO remove
    }
}

//void CDevice::pollGUID() {
//    CCanBuffer buffer;
//    buffer.insertId((unsigned char) category);
//    buffer.insertCommand(CMD_POLL_GUID);
//    buffer.buildBuffer();
//    canbusProtocol->sendCanFrame(buffer);
//}

//void CDevice::getGUIDs() {
//    GUIDs.clear();
//    CCanBuffer buffer;
//    CTimeOut tout;
//    tout.SetMilliSec(200);
//    while (!tout.IsTimeOut()) {
//        buffer = canbusProtocol->getCanFrame();
//        cout<<"getCanFrame: ";
//        buffer.printBuffer();
//        cout<<endl;
//        
//        if (CMD_POLL_GUID == buffer.frameCommand() && static_cast<unsigned int> (category) == buffer.sourceId()) {
//            GUIDs[buffer.getGUID()] = buffer.getNmbDevices();
//            cout << "> received new GUID: " << hex << (int) buffer.getGUID() << dec << ", nmb devs: " << (int) buffer.getNmbDevices() << endl;
//            sendPollACK(buffer.getGUID());
//            tout.SetMilliSec(200);
//        }
//    }
//}

//void CDevice::sendPollACK(unsigned int guid) {
//    CCanBuffer buffer;
//    buffer.insertCommand(CMD_ACK);
//    buffer.insertId((unsigned char) category);
//    buffer << (unsigned char) (guid >> 24);
//    buffer << (unsigned char) (guid >> 16);
//    buffer << (unsigned char) (guid >> 8);
//    buffer << (unsigned char) (guid >> 0);
//    buffer.buildBuffer();
//    canbusProtocol->sendCanFrame(buffer);
//}

void CDevice::assignAddress() {
    CTimeOut tout;
    CCanBuffer buffer;
    unsigned char address;


    for (auto &guid : GUIDs) {
        for (size_t cnt = 0; cnt < guid.second; cnt++) {
            cout << "guid: " << guid.first << ", cnt" << guid.second << ", iteration: " << cnt + 1 << endl;     //@TODO remove
            address = getNewAddress();
            cout << "new address: " << (int) address << endl;           //@TODO remove

            buffer.clear();
            buffer.insertCommand(CMD_SET_ADDRESS);
            buffer.insertId((unsigned char) category);
            buffer << (unsigned char) (guid.first >> 24);
            buffer << (unsigned char) (guid.first >> 16);
            buffer << (unsigned char) (guid.first >> 8);
            buffer << (unsigned char) (guid.first >> 0);
            buffer << (unsigned char) address;
            buffer << (unsigned char) cnt;
            buffer.buildBuffer();
            buffer = canbusProtocol->request(buffer);
            insertDevice(guid.first, cnt, category, address);
            if (CMD_ACK == buffer.frameCommand() && address == buffer.sourceAddress()) {
                cout << "ACK from device CAT: " << (int) buffer[0] << ", ADR: " << (int) buffer[2] << endl; //@TODO remove
            }

        }
    }

    checkDevicesAvailability();
    synchronizeDBdevices();
}

void CDevice::checkDevicesAvailability() {
    vector<unsigned char>unvlbAddresses;

    for (auto &device : devicesDescriptionList) {
        if (!ping(device)) {
            cout << "device to remove address: " << (int) device.address << endl;
            unvlbAddresses.push_back(device.address);
        }
    }
    for (auto &adr : unvlbAddresses) {
        removeDevice(adr);
        try {
            devicesDB->clearDeviceAddress((unsigned char) category, adr);
        } catch (string e) {
            log->error("Cannot clear device's address in database: " + e);
        }
    }
}

void CDevice::synchronizeDBdevices() {
    sortDevicesList(devicesDescriptionList);
    Devices dbDevices;
    unsigned char size;
    unsigned int index = 0;
    try {
        while (index < devicesDescriptionList.size()) {
            size = getDeviceGroupSize(devicesDescriptionList, devicesDescriptionList[index].guid, category);
            dbDevices = devicesDB->getDevices(devicesDescriptionList[index].guid, (unsigned char) category);
           
            if (dbDevices.size() > 0) {
                if (size != dbDevices.size()) {
                    log->error("Different devices recognized with GUID: " + to_string(devicesDescriptionList[index].guid));
                    index += size;
                    continue;
                } else {
                    for (unsigned int i = index; i < (size + index); i++) {
                        synchronizeDeviceName(devicesDescriptionList[i], getDeviceName(devicesDescriptionList[i].guid, devicesDescriptionList[i].luid, category, dbDevices), category, devicesDescriptionList);
                        setDeviceAddress(devicesDescriptionList[i].guid, devicesDescriptionList[i].luid, category, devicesDescriptionList[i].address, dbDevices);
                    }
                    devicesDB->updateDevicesGroup(dbDevices);
                }

            } else {
                for (unsigned int i = index; i < (index + size); i++) {
                    devicesDB->addDevice(devicesDescriptionList[i]);
                }
            }
            index += size;
        }
    } catch (string e) {
        log->error("Cannot synchronize devices list: " + e);
    }

}

unsigned char CDevice::getDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList) {
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == guid && device.luid == luid && device.category == category) {
            return device.address;
        }
    }

    return 0;
}

SDeviceDescription CDevice::getDeviceWithAddress(unsigned char address) {
    for (SDeviceDescription device : devicesDescriptionList) {
        if (device.address == address)
            return device;
    }
    SDeviceDescription dev;
    return dev;

}

void CDevice::setDeviceAddress(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address, Devices &devicesList) {
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == guid && device.luid == luid && device.category == category) {
            device.address = address;
            return;
        }
    }
}

string CDevice::getDeviceName(unsigned int guid, unsigned char luid, EDeviceCategory category, Devices devicesList) {
    string name = "";
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == guid && device.luid == luid && device.category == category) {
            name = device.name;
        }
    }

    return name;
}

unsigned char CDevice::getDeviceGroupSize(Devices devicesList, unsigned int guid, EDeviceCategory category) {
    unsigned char size = 0;
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == guid && device.category == category)
            size++;
    }
    return size;
}

void CDevice::sortDevicesList(Devices &devices) {
    map<unsigned int, Devices> devicesMap;
    for (auto &device : devices) {
        devicesMap[device.guid].push_back(device);
    }
    devices.clear();
    for (map<unsigned int, Devices>::iterator iter = devicesMap.begin(); iter != devicesMap.end(); ++iter) {
        for (auto &device : (iter->second)) {
            devices.push_back(device);
        }

    }
}

void CDevice::insertDevice(unsigned int guid, unsigned char luid, EDeviceCategory category, unsigned char address) {
    SDeviceDescription devDescr;
    devDescr.address = address;
    devDescr.category = category;
    devDescr.guid = guid;
    devDescr.luid = luid;

    devicesDescriptionList.push_back(devDescr);
}

void CDevice::removeDevice(unsigned char address) {
    Devices::iterator device = devicesDescriptionList.begin();
    while (device != devicesDescriptionList.end()) {
        if ((*device).address == address) {
            devicesDescriptionList.erase(device);
            return;
        }
        device++;
    }
}

unsigned char CDevice::getAddress(SDeviceDescription device) {
    for (SDeviceDescription dev : devicesDescriptionList) {
        if (dev == device) {
            return dev.address;
        }
    }
    log->error("No address found for device " + to_string(device));
    return 0;
}

bool CDevice::ping(SDeviceDescription device) {
    unsigned char address = getAddress(device);
    cout << "ADR: " << (int) address << ", CAT: " << (int) category << endl;
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_PING);
    buffer << (unsigned char) address;
    buffer.buildBuffer();
    buffer = canbusProtocol->request(buffer);
    if (CMD_ACK == buffer.frameCommand() && address == buffer.sourceAddress()){
        return true;
    }
    return false;
}

void CDevice::setDeviceName(SDeviceDescription description, string name) {


    description.name = name;

    try {
        devicesDB->setDeviceName(description);
    } catch (string e) {
        log->error("Cannot save device's name in database: " + e);
        return;
    }
    synchronizeDeviceName(description, name, category, devicesDescriptionList);

}

void CDevice::synchronizeDeviceName(SDeviceDescription description, string name, EDeviceCategory category, Devices &devicesList) {
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == description.guid && device.luid == description.luid && device.category == category) {
            device.name = name;
            return;
        }
    }
    log->error("Cannot set name, no device found");
}

void CDevice::listAddresses() {
    if (devicesDescriptionList.size() > 0) {
        log->info("List of devices in category " + to_string(category) + ":");
        for (auto &dev : devicesDescriptionList) {
            log->info(to_string(dev));
        }
    } else {
        log->info("No devices in category " + to_string(category));
    }
}

Devices CDevice::getLogicalDevies() {
    return devicesDescriptionList;
}

void CDevice::resetAllDevicesStatus() {
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_RESET_ALL_STAT);
    buffer.buildBuffer();
    canbusProtocol->send(buffer);
}

void CDevice::checkNewDevicesStatus(){
    if (isSensorDevice()) {
        CCanBuffer buffer;
        CanBuffers stats;
        buffer.insertId((unsigned char) category);
        buffer.insertCommand(CMD_REQ_NEW_STAT);
        buffer.buildBuffer();
        stats = canbusProtocol->broadcastRequest<unsigned char>(buffer, &CCanBuffer::sourceAddress);
        for (CCanBuffer buf : stats){
            if (CMD_REQ_NEW_STAT == buf.frameCommand()) {
                sensorEvent(getDeviceWithAddress(buf.sourceAddress()), buf.getSensorCommand(), buf.getSensorParams());
            }
        }
    }
}

//void CDevice::requestNewDevicesStatus() {
//    if (isSensorDevice()) {
//        CCanBuffer buffer;
//        buffer.insertId((unsigned char) category);
//        buffer.insertCommand(CMD_REQ_NEW_STAT);
//        buffer.buildBuffer();
//        canbusProtocol->send(buffer);
//    }
//}
//
//void CDevice::getNewDevicesStatus() {
//    if (isSensorDevice()) {
//        CCanBuffer buffer;
//        CTimeOut tout;
//        tout.SetMilliSec(200);
//        while (!tout.IsTimeOut()) {
//            buffer = canbusProtocol->getCanFrame();
//            if (CMD_REQ_NEW_STAT == buffer.frameCommand()) {
//                log->put("REC BUFFER IN CAT " + to_string((int) category) + ": ", CLog::LOW_LEVEL_DEBUG);
//                buffer.printBuffer();
//                sendACK(getDeviceWithAddress(buffer.sourceAddress()));
//                tout.SetMilliSec(200);
//            }
//        }
//    }
//}

void CDevice::sendACK(SDeviceDescription device) {
    log->put("Send ACK to: " + to_string(device));
    CCanBuffer buffer;
    buffer.insertCommand(CMD_ACK);
    buffer.insertId((unsigned char) category);
    buffer.insertDestinationAddress(device.address);
    buffer.buildBuffer();
    buffer.printBuffer();
    canbusProtocol->send(buffer);
}

void CDevice::executeAction(SDeviceDescription device, Command command, Blob params) {
    if (actionsMap.find(command) == actionsMap.end()) {
        log->warning("No function [" + to_string((int) command) + "] to invoke");
        return;
    }
    if (command < GLOBAL_ACTION_LIMIT) {
        executeGlobalAction(command, params);
        return;
    }
    for (SDeviceDescription dev : getLogicalDevies()) {
        if (dev == device) {
//            cout << "device found" << endl;
            (actionsMap[command])(device, params);
            return;
        }
    }
    log->error("Device " + to_string(device) + " not found");


}


void CDevice::executeAction(SAction action){
    executeAction(action.device, action.command, action.params);
}

void CDevice::executeGlobalAction(Command command, Blob params) {
    SDeviceDescription empty;
    actionsMap[command](empty, params);
}

void CDevice::reset(SDeviceDescription dev, Blob params) {
    log->info("Reset device addresses in category " + to_string(category));
    resetAddresses();
}

void CDevice::search(SDeviceDescription dev, Blob params) {
    log->info("Start searching devices in category " + to_string(category));
    findGUIDs();
//        pollGUID();
//        getGUIDs();
    assignAddress();
    listAddresses();
}

void CDevice::check(SDeviceDescription dev, Blob params) {
    log->info("Check devices availability in category " + to_string(category));
    checkDevicesAvailability();
}

void CDevice::setName(SDeviceDescription dev, Blob params) {
    string name = params[BLOB_DEVICE_NAME].get<string>();
    log->info("Set new name >> " + name + " << for device " + to_string(dev));
    setDeviceName(dev, name);
}

void CDevice::pingLogicalDevice(SDeviceDescription dev, Blob params) {
    if (ping(dev)) {
        log->info("PING device " + to_string(dev) + " OK");
    } else {
        log->error("PING device " + to_string(dev) + " FAILED");
    }
}

void CDevice::list(SDeviceDescription dev, Blob params) {
    listAddresses();
}

void CDevice::resetStatuses(SDeviceDescription dev, Blob params) {
    resetAllDevicesStatus();
}

void CDevice::checkNewStatuses(SDeviceDescription dev, Blob params) {
    checkNewDevicesStatus();
}

CCan232 *CDevice::getProtocol() {
    return canbusProtocol;
}