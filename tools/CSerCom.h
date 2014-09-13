

#ifndef _CSERCOM_H
#define	_CSERCOM_H

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/types.h>
//#include "CLog.h"
#include <syscall.h>
#include <iostream>
#include <string>
#include <fstream>
#include "CBuffer.h"

using namespace std;

#define PORT_NAME_LEN 256

class CSerCom {
public:


    CSerCom();
    CSerCom(CSerCom& orig);
    virtual ~CSerCom();
    int openSerial(string PortName, long Baud = 9600, int DBits = 8, int SBits = 2, int Parity = 0, int Mode = 0);
    void closePort();

    bool isOpen() {
        return m_PortFd != -1 ? true : false;
    };
    
    unsigned char receiveByte(int timeOut = 50);

    int sendBuffer(CBuffer &);
    int sendBuffer(unsigned char * Buffer, int Len);

    int flushReceiveBuffer(void);
private:


    int openTermio();
    char m_PortName[PORT_NAME_LEN + 1];
    long m_Baud;
    long m_DBits;
    long m_SBits;
    long m_ParityOn;
    long m_ParityMode;
    long m_Mode;
    long m_PortFd;
    int m_RxTout;
    struct termios m_OldTio, m_ActTio;
};



#endif	/* _CSERCOM_H */
