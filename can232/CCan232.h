/* 
 * File:   CCan232.h
 * Author: Jezierski
 *
 * Created on 1 czerwiec 2013, 20:08
 */

#ifndef CCAN232_H
#define	CCAN232_H

#include <iostream>
#include <mutex>
#include <vector>

#include "../tools/CSerCom.h"
#include "../tools/CBuffer.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CTools.h"
#include "../tools/CConfiguration.h"
#include "../tools/CLog.h"
#include "../tools/CTimeOut.h"

#define TOUT_BROADCAST  10             //@TODO try set shorter

#define HEADER  '?'
#define CMD_SEND        'T'
#define CMD_REQUEST     'G'
#define CR      0x0d
#define CMD_INIT        "Init"


using namespace std;

enum class ECanBaudRate {
    BPS640000 = 1,
            BPS320000 = 2,
            BPS160000 = 3,
            BPS80000 = 4,
            BPS40000 = 5,
            BPS20000 = 6,
            BPS10000 = 7,
};

class CCan232 : public CSerCom {
public:
    CCan232();
    //    CCan232(const CCan232& orig);
    virtual ~CCan232();

    bool initCan232Device();

    void send(CCanBuffer &frame);
    CCanBuffer request(CCanBuffer &frame);

    template <class ret>
    CanBuffers broadcastRequest(CCanBuffer &frame, ret(CCanBuffer::*ackFunction)()) {
        lock_guard<mutex> lock(barrier);
        sendCanFrame(frame);
        CCanBuffer buffer, sendBuffer;
        CanBuffers buffers;
        CTimeOut tout;
        tout.SetMilliSec(TOUT_BROADCAST);
        while (!tout.IsTimeOut()) {
            buffer = getCanFrame();

            if (frame.frameCommand() == buffer.frameCommand() && frame.frameId() == buffer.sourceId()) {
                buffers.push_back(buffer);
                sendBuffer.clear();
                sendBuffer.insertCommand(CMD_ACK);
                sendBuffer.insertId(frame.frameId());
                ret returnData = (buffer.*ackFunction)();
                for (size_t i = sizeof (ret); i > 0; i--) {
                    sendBuffer << (unsigned char) (returnData >> ((i - 1) * 8));
                }
                sendBuffer.buildBuffer();
                sendCanFrame(sendBuffer);
                tout.SetMilliSec(TOUT_BROADCAST);
            }
        }
        return buffers;
    }




    //    typedef void (CCanBuffer::*ackFunction)(); // type for conciseness

private:
    void connect(void);
    void restoreDefaults();
    void openCAN();
    void closeCAN();
    void setSpeed(ECanBaudRate baudRate);
    void setSpeed(string baudRate);
    bool handshake();
    void setAcceptedMask(unsigned char maskId, unsigned int mask);
    void setAcceptedFilters(unsigned char filterId, unsigned int filter);


    CCanBuffer getCanFrame();
    void sendCanFrame(CCanBuffer &frame);
    unsigned char getCRC(CBuffer &buffer);
    unsigned char checkCRC(CBuffer& buffer);
    bool isFrameComplete(CBuffer &frame);\
    bool setCommand(CBuffer &buffer);
    CBuffer getFrame();
    CCanBuffer createCanBuffer(CBuffer &buffer);

    CConfiguration *config;
    CLog *log;
    mutex barrier;
};

#endif	/* CCAN232_H */

