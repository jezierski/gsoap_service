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
    addAction(this, ACTION_BOOT, &CDevice::bootDevice);
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

vector<string> CDevice::getFirmwareFilesList() {
    CFirmwareLoader loader;

    vector<string> fileList = loader.getFileList();
    return fileList;
}

void CDevice::uploadFirmware(string fileName) {
    //quiet other devices


    CFirmwareLoader loader;
    CFirmwareBuffer firmware;
    unsigned int crc;

    try {

        firmware = loader.readFile(fileName);
        clearFlash();
        initSelfCRC();
        log->info("Start a firmware uploading...");
        crc = uploadFirmware(firmware);
        verifyFirmware(crc);
        uploadExFirmware(firmware);
        setGuidIfNeed();
        exitBootMode();
        log->info("Upload firmware success");
    } catch (string e) {
        log->error("Firmware upload failed: " + e);
    }

}

void CDevice::setGuidIfNeed() {
    log->info("Checking device's guid...");
    int guid = readGUID();
    if (guid == -1) {
        log->info("Setting new guid");
        writeGUID();
    }
}

void CDevice::uploadExFirmware(CFirmwareBuffer &buffer) {
    unsigned char exQnty = buffer.getExBufferQnty();
    CFirmwareBuffer exBuffer;
    for (unsigned char index = 0; index < exQnty; index++) {
        log->info("Extended firmware data uploading (" + to_string((int) index + 1) + "/" + to_string((int) exQnty) + ")...");
        exBuffer = buffer.getExBuffer(index);
        uploadFirmware(exBuffer);
    }
}

int CDevice::readGUID() {
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_GET_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_AUTO_ERASE | BOOT_AUTO_INC);
    buffer.insertBootCommand(BOOT_CMD_GET_UID);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);

    return buffer.getBootGUID();

}

void CDevice::initWriteGUID() {

    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_SET_UID);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Init writing GUID failed");
    }


}

void CDevice::writeGUID() {
    int guid = generateGUID();
    initWriteGUID();
    CBuffer data;
    data << ((guid >> 16) & 0xffff);
    data << (guid & 0xffff);
    writeProgramData(data);

}

unsigned int CDevice::uploadFirmware(CFirmwareBuffer &firmware) {
    CFirmwareBuffer tempBuffer;
    unsigned int lastAddress = 0;
    unsigned char progress = 255;
    unsigned int crc = 0;

    tempBuffer = firmware.getNotNullDataBlock();
    while (tempBuffer.getLength()) {
        if (tempBuffer.getDataBlockAddress() != lastAddress + 8) {
            initBootWrite(tempBuffer.getDataBlockAddress());
        }
        lastAddress = tempBuffer.getDataBlockAddress();
        //        cout<<"LAST ADDRESS: "<<lastAddress<<endl;
        writeProgramData(tempBuffer);
        calcCRC(crc, tempBuffer);
        tempBuffer = firmware.getNotNullDataBlock();
        if (progress != firmware.getReadingProgress()) {
            progress = firmware.getReadingProgress();
            log->info("Upload progress: " + to_string((int) progress) + "%");
        }
    }
    return crc;
}

void CDevice::calcCRC(unsigned int &crc, CFirmwareBuffer buf) {
    for (size_t i = 0; i < buf.getLength(); i++) {
        crc += buf[i];
        crc &= 0xffff;
    }
}

void CDevice::verifyFirmware(unsigned int crc) {
    log->info("Verifying firmware...");

    unsigned int devCRC = getSelfCRC();
    if (crc != devCRC) {
        throw string("Veryfication firmware failed");
    }

}

void CDevice::initBootWrite(unsigned int address) {
    //    cout<<"INIT WRITE ADR: "<<address<<endl;
    //CCanBuffer recBuf;
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(address);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_INIT_WRITE);
    buffer.buildBootBuffer();

	buffer = canbusProtocol->request(buffer);
    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Writing boot init failed");
    }

    //int i = 20;
    //do {
    //    recBuf = canbusProtocol->request(buffer);
    //} while (i-- && recBuf[0] != BOOT_COMMAND_ACK);

    //if (recBuf[0] != BOOT_COMMAND_ACK) {
    //    throw string("Writing boot init failed");
    //}
}

void CDevice::initBootRead(unsigned int address) {
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(address);
    buffer.insertBootControlBits(BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_INIT_READ);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Reading boot init failed");
    }
}

void CDevice::initSelfCRC() {
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_INIT_CHK);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Self CRC init failed");
    }
}

unsigned int CDevice::getSelfCRC() {
    //CCanBuffer recBuf;
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_GET_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(0);
    buffer.insertBootCommand(BOOT_CMD_CHK_RUN);
    buffer.buildBootBuffer();

	buffer = canbusProtocol->request(buffer);

    return buffer.getBootCRC();

    //int i = 100;
    //do {
    //    cout << "try getSelfCRC" << endl;
    //    recBuf = canbusProtocol->request(buffer);
    //    recBuf.printBuffer();
    //} while (i-- && (recBuf.getLength() == 0 || recBuf[0] == BOOT_COMMAND_ACK));


    //return recBuf.getBootCRC();
}

void CDevice::writeProgramData(CBuffer data) {

    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_DATA);
    buffer << data;
    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Writing program data failed");
    }
}

CCanBuffer CDevice::readProgramData() {
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_GET_DATA);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);
    //    cout << "received buffer: " << endl; //@TODO remove it
    //    buffer.printBuffer(); //@TODO remove it
    return buffer;
}

void CDevice::exitBootMode() {
    log->info("Exiting BOOT mode...");
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_EXIT_BOOT);
    buffer.buildBootBuffer();
    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Exit boot mode failed");
    }
    resetDevice();

}

void CDevice::resetDevice() {
    log->info("Reseting device...");
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_RESET);
    buffer.buildBootBuffer();
    canbusProtocol->send(buffer);
}

bool CDevice::checkReady() {
    log->info("Checking if device is ready...");
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_GET_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_GET_READY);
    buffer.buildBootBuffer();

    buffer = canbusProtocol->request(buffer);

    return (buffer[0] == BOOT_COMMAND_ACK);
}

void CDevice::getDummyFrames() {
    CCanBuffer buffer;
    CBuffer rec;
    //int i = 20;
    do {
        rec = canbusProtocol->request(buffer);
    } while (rec.getLength()); //i--); //rec.getLength());
}

void CDevice::clearFlash() {
    log->info("Reseting program memory...");
    CTimeOut tout;
    CCanBuffer buffer;
    buffer.insertId(0x330 | BOOT_PUT_CMD);
    buffer.insertFlashAddress(0);
    buffer.insertBootControlBits(BOOT_WRITE_UNLOCK | BOOT_AUTO_ERASE | BOOT_AUTO_INC | BOOT_SEND_ACK);
    buffer.insertBootCommand(BOOT_CMD_CLR_PROG);
    buffer.buildBootBuffer();

    buffer = canbusProtocol->request(buffer);

    if (buffer[0] != BOOT_COMMAND_ACK) {
        throw string("Reseting program memory failed");
    }


    tout.SetMilliSec(5000);
    while (!tout.IsTimeOut()) {
        if (checkReady()) {
            getDummyFrames();
            log->info("Reseting program memory complete");
            return;
        }
        msleep(300);
    }

    throw string("Reseting program memory failed");
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

bool CDevice::resetAddresses() {
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
        return false;
    }
    return true;
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
        log->info("Received new GUID: " + to_string((int) buf.getGUID()) + " [" + to_string((int) buf.getGUID(), true) + "], number of local devices: " + to_string((int) buf.getNmbDevices()));
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
            //            cout << "guid: " << guid.first << ", cnt" << guid.second << ", iteration: " << cnt + 1 << endl; //@TODO remove
            address = getNewAddress();
            //            cout << "new address: " << (int) address << endl; //@TODO remove
            log->info("Set address " + to_string((int) address) + " for device with GUID: " + to_string((int) guid.first) + ":" + to_string(cnt));
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
                //                cout << "ACK from device CAT: " << (int) buffer[0] << ", ADR: " << (int) buffer[2] << endl; //@TODO remove
                log->success("Received ACK from device with GUID: " + to_string((int) guid.first) + ":" + to_string(cnt) + " and new address: " + to_string((int) buffer[2]));
            }

        }
    }

    checkDevicesAvailability();
    synchronizeDBdevices();
}

Blob CDevice::checkDevicesAvailability() {
    vector<unsigned char>unvlbAddresses;
    Blob b;
        string response = "";
        for (auto &device : devicesDescriptionList) {
            if (!ping(device)) {
                unvlbAddresses.push_back(device.address);
            }
        }
        for (auto &adr : unvlbAddresses) {
            removeDevice(adr);
            try {
                devicesDB->clearDeviceAddress((unsigned char) category, adr);
            } catch (string e) {
                response += "Cannot clear device's address in database: " + e + "\n";
                log->error(response);
            }
        }
        if (response == "")
            response = "OK";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
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
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_PING);
    buffer << (unsigned char) address;
    buffer.buildBuffer();
 
    buffer = canbusProtocol->request(buffer);

    if (CMD_ACK == buffer.frameCommand() && address == buffer.sourceAddress()) {
        return true;
    }
    return false;
}

Blob CDevice::setDeviceName(SDeviceDescription description, string name) {

    Blob b;
    string response = "OK";
    description.name = name;

    try {
        devicesDB->setDeviceName(description);
    } catch (string e) {
        response = "Cannot save device's name in database: " + e;
        log->error(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    b = synchronizeDeviceName(description, name, category, devicesDescriptionList);
    return b;
}

Blob CDevice::synchronizeDeviceName(SDeviceDescription description, string name, EDeviceCategory category, Devices &devicesList) {
    Blob b;
    string response = "OK";
    for (SDeviceDescription &device : devicesList) {
        if (device.guid == description.guid && device.luid == description.luid && device.category == category) {
            device.name = name;
            b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
            return b;
        }
    }
    response = "Cannot set name, no device found";
    log->error(response);
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CDevice::listAddresses() {
    if (devicesDescriptionList.size() > 0) {
        log->info("List of devices in category " + to_string(category) + ":");
        for (auto &dev : devicesDescriptionList) {
            log->info(to_string(dev));
        }
    } else {
        log->info("No devices in category " + to_string(category));
    }
    Blob b;
    b[BLOB_DEVICES_LIST].put<Devices>(devicesDescriptionList);
    return b;
}

Devices CDevice::getLogicalDevies() {
    return devicesDescriptionList;
}

bool CDevice::resetAllDevicesStatus() {
    CCanBuffer buffer;
    buffer.insertId((unsigned char) category);
    buffer.insertCommand(CMD_RESET_ALL_STAT);
    buffer.buildBuffer();
    return canbusProtocol->send(buffer);
}

void CDevice::checkNewDevicesStatus() {
    if (isSensorDevice()) {
        CCanBuffer buffer;
        CanBuffers stats;
        buffer.insertId((unsigned char) category);
        buffer.insertCommand(CMD_REQ_NEW_STAT);
        buffer.buildBuffer();
        stats = canbusProtocol->broadcastRequest<unsigned char>(buffer, &CCanBuffer::sourceAddress);
        for (CCanBuffer buf : stats) {
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

Blob CDevice::executeAction(SDeviceDescription device, Command command, Blob params) {
    Blob b;
    string response;
    if (actionsMap.find(command) == actionsMap.end()) {
        response = "No function [" + to_string((int) command) + "] to invoke";
        log->warning(response);
        b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
        return b;
    }
    if (command < GLOBAL_ACTION_LIMIT) {
        return executeGlobalAction(command, params);
    }
    for (SDeviceDescription dev : getLogicalDevies()) {
        if (dev == device) {
            //            cout << "device found" << endl;
            return (actionsMap[command])(device, params);
        }
    }
    response = "Device " + to_string(device) + " not found";
    log->error(response);
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;

}

Blob CDevice::executeAction(SAction action) {
    return executeAction(action.device, action.command, action.params);
}

Blob CDevice::executeGlobalAction(Command command, Blob params) {
    SDeviceDescription empty;
    return actionsMap[command](empty, params);
}

Blob CDevice::reset(SDeviceDescription dev, Blob params) {
    log->info("Reset device addresses in category " + to_string(category));
    Blob b;
    string response;
    response = (resetAddresses()) ? "OK" : "Reset devices failed";
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CDevice::search(SDeviceDescription dev, Blob params) {
    log->info("Start searching devices in category " + to_string(category));
    findGUIDs();

    assignAddress();
    return listAddresses();
}

Blob CDevice::check(SDeviceDescription dev, Blob params) {
    log->info("Check devices availability in category " + to_string(category));
    return checkDevicesAvailability();
}

Blob CDevice::setName(SDeviceDescription dev, Blob params) {
    Blob b;
    string name = params[BLOB_DEVICE_NAME].get<string>();
    log->info("Set new name >> " + name + " << for device " + to_string(dev));
    b = setDeviceName(dev, name);
    return b;
}

Blob CDevice::pingLogicalDevice(SDeviceDescription dev, Blob params) {
    Blob b;
    string response = "OK";
    if (ping(dev)) {
        log->info("PING device " + to_string(dev) + " OK");
    } else {
        response = "PING device " + to_string(dev) + " FAILED";
        log->error(response);
    }
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CDevice::bootDevice(SDeviceDescription dev, Blob params) {
    //    Params par = params[BLOB_ACTION_PARAMETER].get<Params>();
    string response;
    Blob b;

    CCanBuffer buffer;

    buffer.insertCommand(CMD_ENTER_BOOT);
    buffer.insertId((unsigned char) dev.category);
    buffer.buildBuffer();
    response = (getProtocol()->send(buffer)) ? "OK" : "Enter device into boot mode failed";

    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CDevice::list(SDeviceDescription dev, Blob params) {
    return listAddresses();
}

Blob CDevice::resetStatuses(SDeviceDescription dev, Blob params) {
    Blob b;
    string response;
    response = (resetAllDevicesStatus()) ? "OK" : "Reset device's [ " + to_string(dev.category) + " ] statuses failed";
    b[BLOB_TXT_RESPONSE_RESULT].put<string>(response);
    return b;
}

Blob CDevice::checkNewStatuses(SDeviceDescription dev, Blob params) {
    checkNewDevicesStatus();
    Blob b;
    return b;
}

CCan232 *CDevice::getProtocol() {
    return canbusProtocol;
}