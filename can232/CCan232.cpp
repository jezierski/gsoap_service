/* 
 * File:   CCan232.cpp
 * Author: Jezierski
 * 
 * Created on 1 czerwiec 2013, 20:08
 */

#include "CCan232.h"
#include "../tools/CTimeOut.h"



#define portName "/dev/ttyAMA0"         //@TODO move to DB

CCan232::CCan232() {
}

//CCan232::CCan232(const CCan232& orig) {
//}

CCan232::~CCan232() {
}

void CCan232::connect() {

    openSerial(portName, 115200, 8, 1, 0);

}

void CCan232::openCAN() {

    CBuffer buffer;
    buffer << "O";
    buffer << (unsigned char) 0x0d; //@TODO make constans
    setCommand(buffer);
}

void CCan232::closeCAN() {

    CBuffer buffer;
    buffer << "C";
    buffer << (unsigned char) 0x0d; //@TODO make constans
    setCommand(buffer);
}

void CCan232::setSpeed(ECanBaudRate baudRate) {
    CBuffer buffer;
    buffer << "S";
    buffer << (unsigned char) baudRate;
    setCommand(buffer);
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
            sendBuffer(buffer);
            buffer.clear();
            buffer << (unsigned char) 0x0d; //@TODO make const
            sendBuffer(buffer);
            rb = receiveByte();

            if ('!' == rb) {
                return true;
            }
        } catch (string e) {
            cout << e << endl;
        }
    }
    //    log->put();
    cout << "Can232 device handshake failed" << endl;
    return false;
}

void CCan232::restoreDefaults(){
    CBuffer buffer;
    buffer << "Init";           //@TODO make const
    setCommand(buffer);
}

bool CCan232::setCommand(CBuffer &buffer) {
    CBuffer buf;
    buf << "?"; //@TODO make const
    buf << buffer;
    buf << (unsigned char) 0x0d; //@TODO make const
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady() && buf.isACK())
            return true;

    } catch (string e) {
        //log->put();)
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
        setSpeed(ECanBaudRate::BPS160000); // @TODO read from DB
        setAcceptedMask(0, 2); // @TODO read from DB
        setAcceptedMask(1, 2); // @TODO read from DB
        setAcceptedFilters(0, 2); // @TODO read from DB
        setAcceptedFilters(1, 2); // @TODO read from DB
        setAcceptedFilters(2, 2); // @TODO read from DB
        setAcceptedFilters(3, 2); // @TODO read from DB
        setAcceptedFilters(4, 2); // @TODO read from DB
        setAcceptedFilters(5, 2); // @TODO read from DB
        openCAN();
    } catch (string e) {
        //log->put();
        cout << "Can232 device initialization failed: " << e << endl;
        return false;
    }
    //log->put();
    cout << "Can232 device initialization success" << endl;
    return true;
}

void CCan232::sendCanFrame(CCanBuffer &frame) {
    CBuffer buf;
    buf << "?"; //@TODO make const
    buf << "T"; //@TODO make const
    buf << frame.frameId();
    buf << (unsigned char) frame.getLength();
    buf << frame;
    buf << getCRC(buf);
    buf << (unsigned char) 0x0d; //@TODO make const
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady()) {
            if (buf.getErrorCode()) {
                //                log->put();
                cout << "Sending can frame error code: " << (int) buf.getErrorCode() << endl;
            }
        }

    } catch (string e) {
        //log->put();)
        cout << "Sending CAN frame failed: " << e << endl;
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

    cout<<"crc: "<<(int)crc<<endl;
    return (0 == crc);
}

CBuffer CCan232::getFrame() {
    CBuffer buf;
    CTimeOut tout;
    unsigned char rbyte;

    rbyte = receiveByte();
    cout << "------rbyte: " << rbyte << ", int: " << (int) rbyte << ", hex: " << hex << (int) rbyte << dec << endl;
    if (rbyte != 'T') { //@TODO make const
        return buf;
    }

    buf << (unsigned char) rbyte;
    tout.SetMilliSec(1000);
    while (!tout.IsTimeOut()) {
        buf << (unsigned char) receiveByte();
        cout << "------buf: " << buf[buf.getLength() - 1] << ", int: " << (int) buf[buf.getLength() - 1] << ", hex: " << hex << (int) buf[buf.getLength() - 1] << dec << endl;
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
    buf << "?"; //@TODO make const
    buf << "G"; //@TODO make const
    buf << 0x0d; //@TODO make const
    try {
        sendBuffer(buf);
        buf = getFrame();
        if (buf.isReady()) {
            canBuffer = createCanBuffer(buf);
        }

    } catch (string e) {
        //log->put();)
        cout << "Receiving CAN frame failed: " << e << endl;
    }
    
    
    return canBuffer;
}

CCanBuffer CCan232::createCanBuffer(CBuffer &buffer){
    CCanBuffer canBuffer;
    unsigned int id;
    if (!checkCRC(buffer)){
//        log->put();
        cout<<"Received CAN frame CRCfailed"<<endl;
        return canBuffer;
    }
    id = (buffer[1] << 8) & 0xff00;
    id |= buffer[2];
    canBuffer.insertId(id);
    for (size_t i = 0; i < buffer[3]; i++)
        canBuffer << (unsigned char)buffer[i + 4];
    
    return canBuffer;
    
}