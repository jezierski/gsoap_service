/* 
 * File:   CCan232.cpp
 * Author: Jezierski
 * 
 * Created on 1 czerwiec 2013, 20:08
 */

#include "CCan232.h"
#include "../tools/CTimeOut.h"

CCan232::CCan232() {
    
    config = CConfiguration::getInstance();
    log = CLog::getInstance();
}

//CCan232::CCan232(const CCan232& orig) {
//}

CCan232::~CCan232() {
}

void CCan232::connect() {

    openSerial(config->getList<string>("can232")["portName"], 115200, 8, 1, 0);

}

void CCan232::openCAN() {

    CBuffer buffer;
    buffer << "O";
    setCommand(buffer);
}

void CCan232::closeCAN() {

    CBuffer buffer;
    buffer << "C";
    setCommand(buffer);
}

void CCan232::setSpeed(ECanBaudRate baudRate) {
    CBuffer buffer;
    buffer << "S";
    buffer << (unsigned char) baudRate;
    setCommand(buffer);
}

void CCan232::setSpeed(string baudRate) {
    ECanBaudRate bps = ECanBaudRate::BPS10000;
    if (baudRate == "10000")
        bps = ECanBaudRate::BPS10000;
    else if (baudRate == "20000")
        bps = ECanBaudRate::BPS20000;
    else if (baudRate == "40000")
        bps = ECanBaudRate::BPS40000;
    else if (baudRate == "80000")
        bps = ECanBaudRate::BPS80000;
    else if (baudRate == "160000")
        bps = ECanBaudRate::BPS160000;
    else if (baudRate == "320000")
        bps = ECanBaudRate::BPS320000;

    setSpeed(bps);
}

void CCan232::setAcceptedMask(unsigned char maskId, unsigned int mask) {
    CBuffer buffer;
    buffer << "M";
    buffer << (unsigned char) maskId;
    buffer << mask;
    setCommand(buffer);
}

void CCan232::setAcceptedFilters(unsigned char filterId, unsigned int filter) {
    CBuffer buffer;
    buffer << "F";
    buffer << (unsigned char) filterId;
    buffer << filter;
    setCommand(buffer);
}

bool CCan232::handshake() {
    CBuffer buffer;
    CTimeOut tout;
    tout.SetMilliSec(1000);
    unsigned char rb;
    while (!tout.IsTimeOut()) {
        try {
            buffer.clear();
            buffer << "?";
            sendBuffer(buffer);
            buffer.clear();
            buffer << (unsigned char) 4;
            sendBuffer(buffer);
            buffer.clear();
            buffer << "?";
            sendBuffer(buffer);
            buffer.clear();
            buffer << (unsigned char) CR;
            sendBuffer(buffer);
            rb = receiveByte();

            if ('!' == rb) {
                return true;
            }
        } catch (string e) {
            cout << e << endl;
        }
    }
    log->error("Can232 device handshake failed");
    return false;
}

void CCan232::restoreDefaults() {
    CBuffer buffer;
    buffer << CMD_INIT;
    setCommand(buffer);
}

bool CCan232::setCommand(CBuffer &buffer) {
    CBuffer buf;
    buf << (unsigned char) HEADER;
    buf << (unsigned char) (buffer.getLength() + 3);
    buf << buffer;
    buf << (unsigned char) CR;
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady() && buf.isACK())
            return true;

    } catch (string e) {
        throw string("Set command '" + to_string(buffer[0]) + "' failed");
    }
    return false;
}

bool CCan232::isFrameComplete(CBuffer &frame) {
    if (frame[1] >= 0x30)
        return true;
    else
        return (frame[3] == (frame.getLength() - 5));

}

bool CCan232::initCan232Device() {
    try {
        connect();
        handshake();
        restoreDefaults();
        closeCAN();
        setSpeed(config->getList<string>("can232")["CANspeed"]);
        setAcceptedMask(0, config->getList<unsigned int>("canConfig")["acceptMask0"]);
        setAcceptedMask(1, config->getList<unsigned int>("canConfig")["acceptMask1"]);
        setAcceptedFilters(0, config->getList<unsigned int>("canConfig")["acceptFilter0"]);
        setAcceptedFilters(1, config->getList<unsigned int>("canConfig")["acceptFilter1"]);
        setAcceptedFilters(2, config->getList<unsigned int>("canConfig")["acceptFilter2"]);
        setAcceptedFilters(3, config->getList<unsigned int>("canConfig")["acceptFilter3"]);
        setAcceptedFilters(4, config->getList<unsigned int>("canConfig")["acceptFilter4"]);
        setAcceptedFilters(5, config->getList<unsigned int>("canConfig")["acceptFilter5"]);
        openCAN();
    } catch (string e) {
        log->error("Can232 device initialization failed: ");
        return false;
    }
    log->success("Can232 device initialization success");
    return true;
}

void CCan232::sendCanFrame(CCanBuffer &frame) {
//    msleep(10);
    CBuffer buf;
    buf << (unsigned char) HEADER;
    buf << (unsigned char) (frame.getLength() + 8);
    buf << (unsigned char) CMD_SEND;
    buf << frame.frameId();
    buf << (unsigned char) frame.getLength();
    buf << frame;
    buf << (unsigned char) getCRC(buf);
    buf << (unsigned char) CR;
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady()) {
            if (buf.getErrorCode()) {
                log->error("Sending can frame error code: " + to_string((int) buf.getErrorCode()));
            }
        }

    } catch (string e) {
        log->error("Sending CAN frame failed: " + to_string(e));
    }
}

unsigned char CCan232::getCRC(CBuffer& buffer) {
    unsigned char crc = 0x0d;
    for (size_t i = 0; i < buffer.getLength(); i++)
        crc += buffer[i];

    return (256 - crc);
}

unsigned char CCan232::checkCRC(CBuffer& buffer) {
    unsigned char crc = 0;
    for (size_t i = 0; i < buffer.getLength(); i++)
        crc += buffer[i];

//    cout << "crc: " << (int) crc << endl;
    return (0 == crc);
}

CBuffer CCan232::getFrame() {
    CBuffer buf;
    CTimeOut tout;
    unsigned char rbyte;

    rbyte = receiveByte();
//    cout << "--<>--rbyte: " << rbyte << ", int: " << (int) rbyte << ", hex: " << hex << (int) rbyte << dec << endl;
    if (rbyte != CMD_SEND) {
        return buf;
    }

    buf << (unsigned char) rbyte;
    tout.SetMilliSec(1000);
    while (!tout.IsTimeOut()) {
        buf << (unsigned char) receiveByte();
//        cout << "------buf: " << buf[buf.getLength() - 1] << ", int: " << (int) buf[buf.getLength() - 1] << ", hex: " << hex << (int) buf[buf.getLength() - 1] << dec << endl;
        if (isFrameComplete(buf)) {
            buf.setReady();
            return buf;
        }
    };
    buf.clear();
    return buf;
}

CCanBuffer CCan232::getCanFrame() {
    CBuffer buf;
    CCanBuffer canBuffer;
    buf << (unsigned char) HEADER;
    buf << (unsigned char) 4;
    buf << (unsigned char) CMD_REQUEST;
    buf << (unsigned char) CR;
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady()) {
            if (!buf.isNoData()){
                canBuffer = createCanBuffer(buf);
            }
        }

    } catch (string e) {
        log->error("Receiving CAN frame failed: " + to_string(e));
    }


    return canBuffer;
}

CCanBuffer CCan232::createCanBuffer(CBuffer &buffer) {
    CCanBuffer canBuffer;
    unsigned int id;
    if (!checkCRC(buffer)) {
        log->error("Received CAN frame CRCfailed");
        return canBuffer;
    }
    id = (buffer[1] << 8) & 0xff00;
    id |= buffer[2];
    canBuffer.insertId(id);
    for (size_t i = 0; i < buffer[3]; i++)
        canBuffer << (unsigned char) buffer[i + 4];

    return canBuffer;

}