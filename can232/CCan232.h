/* 
 * File:   CCan232.h
 * Author: Jezierski
 *
 * Created on 1 czerwiec 2013, 20:08
 */

#ifndef CCAN232_H
#define	CCAN232_H

#include <iostream>

#include "../tools/CSerCom.h"
#include "../tools/CBuffer.h"
#include "../tools/CCanBuffer.h"
#include "../tools/CTools.h"
#include "../tools/CConfiguration.h"
#include "../tools/CLog.h"


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

    void sendCanFrame(CCanBuffer &frame);
    CCanBuffer getCanFrame();



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

    unsigned char getCRC(CBuffer &buffer);
    unsigned char checkCRC(CBuffer& buffer);
    bool isFrameComplete(CBuffer &frame);
    bool setCommand(CBuffer &buffer);
    CBuffer getFrame();
    CCanBuffer createCanBuffer(CBuffer &buffer);
    
    CConfiguration *config;
    CLog *log;
};

#endif	/* CCAN232_H */

