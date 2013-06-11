

#include "CSerCom.h"
#include "CTimeOut.h"
#include <iostream>
using namespace std;
//mutex serialBarrier;
////////////////////////////////////////////////////////////////////////////////
// class CSerCom

//extern ofstream fileDebug;

CSerCom::CSerCom() {
    //    log = CLog::getInstance();
    m_PortFd = -1;
    //    m_RxTout = RX_TOUT;
}

CSerCom::CSerCom(CSerCom& orig) {
    //    log = CLog::getInstance();
    m_PortFd = orig.m_PortFd;
    //    m_RxTout = RX_TOUT;
}

CSerCom::~CSerCom() {
    closePort();
}
////////////////////////////////////////////////////////////////////////
/// Open termio library functions with private settings.
/// \param none
/// \return 0= ok or error code

int CSerCom::openTermio() {

    m_PortFd = open(m_PortName, O_RDWR | O_NOCTTY | O_NONBLOCK); //set the user console port up
    if (m_PortFd >= 0) {
        tcgetattr(m_PortFd, &m_OldTio); // save current port settings   //so commands are interpreted right for this program
        memset(&m_ActTio, 0, sizeof (struct termios));
        m_ActTio.c_cflag = m_Baud | m_DBits | m_SBits | m_ParityOn | m_ParityMode | CLOCAL | CREAD;
        m_ActTio.c_iflag = IGNPAR;
        m_ActTio.c_oflag = 0;
        m_ActTio.c_lflag = 0; //ICANON;
        m_ActTio.c_cc[VMIN] = 1;
        m_ActTio.c_cc[VTIME] = 0;
        tcflush(m_PortFd, TCIOFLUSH);
        tcsetattr(m_PortFd, TCSANOW, &m_ActTio);


    } else {
        throw string("Cannot open serial port");
    }
    return 0;
    
}

////////////////////////////////////////////////////////////////////////
/// Open serial port with given parameter
/// \param PortName device name as ascii char string
/// \param Baud baudrate as long integer, if the value don't fit default is 9600 Baud
/// \param DBits data bits 5...9, if the value don't fit default is 8 data bits
/// \param SBits stop bist 1,2, if the value don't fit default is 2 stop bits
/// \param Parity default is none
///  - 0= none
///  - 1= odd
///  - 2= even
/// \param Mode not used, free for futher options
/// \return 0= ok or error code

int CSerCom::openSerial(string PortName, long Baud, int DBits, int SBits, int Parity, int Mode) {
    int error = 0;

    if (isOpen())
        closePort();

    Mode = 0; // not used
    memset(m_PortName, 0, sizeof (m_PortName));


    strncpy(m_PortName, PortName.c_str(), PORT_NAME_LEN);

    // Convert Parameter to termio
    switch (Baud) {
        case 230400:
            m_Baud = B230400;
            break;
        case 115200:
            m_Baud = B115200;
            break;
        case 57600:
            m_Baud = B57600;
            break;
        case 38400:
            m_Baud = B38400;
            break;
        case 19200:
            m_Baud = B19200;
            break;
        case 9600:
            m_Baud = B9600;
            break;
        case 4800:
            m_Baud = B4800;
            break;
        case 2400:
            m_Baud = B2400;
            break;
        case 1800:
            m_Baud = B1800;
            break;
        case 1200:
            m_Baud = B1200;
            break;
        case 600:
            m_Baud = B600;
            break;
        case 300:
            m_Baud = B300;
            break;
        case 200:
            m_Baud = B200;
            break;
        case 150:
            m_Baud = B150;
            break;
        case 134:
            m_Baud = B134;
            break;
        case 110:
            m_Baud = B110;
            break;
        case 75:
            m_Baud = B75;
            break;
        case 50:
            m_Baud = B50;
            break;
        default:
            m_Baud = B9600;
            break;
    }


    switch (DBits) {
        case 8:
        default:
            m_DBits = CS8;
            break;
        case 7:
            m_DBits = CS7;
            break;
        case 6:
            m_DBits = CS6;
            break;
        case 5:
            m_DBits = CS5;
            break;
    }

    switch (SBits) {
        case 1:
            m_SBits = 0;
            break;
        default:
        case 2:
            m_SBits = CSTOPB;
            break;
    }

    switch (Parity) {
        case 0:
        default: //none
            m_ParityOn = 0;
            m_ParityMode = 0;
            break;
        case 1: //odd
            m_ParityOn = PARENB;
            m_ParityMode = PARODD;
            break;
        case 2: //even
            m_ParityOn = PARENB;
            m_ParityMode = 0;
            break;
    } //end of switch parity


    error = openTermio();

    return error;
}

////////////////////////////////////////////////////////////////////////
/// Close the serial port
/// \param none
/// \return none

void CSerCom::closePort() {
    if (m_PortFd != -1) {
        tcsetattr(m_PortFd, TCSANOW, &m_OldTio);
        close(m_PortFd);
        m_PortFd = -1;
    }
}

////////////////////////////////////////////////////////////////////////
/// Send one byte
/// \param Byte byte to send
/// \return 0= ok or error code

//int CSerCom::SendByte(unsigned char Byte) {
//    if (IsOpen()) {
//        if (write(m_PortFd, &Byte, 1) != 1) {
//            //error = SetError(SIO_SEND_BYTE_ERR);
//            cout << "$$ throw no.51" << endl;
//            throw_line("Error during sending byte");
//        }
//    } else {
//        //error = SetError(SIO_NOT_OPEN_ERR);
//        cout << "$$ throw no.52" << endl;
//        throw_line("Device's port is not open");
//    }
//
//    return 0;
//}
//
//int CSerCom::countBufferedBytes() {
//
//    int ret;
//    ioctl(m_PortFd, FIONREAD, &ret);
//    return ret;
//}


////////////////////////////////////////////////////////////////////////
/// Receive one Byte
/// \param timeOut timeout in milisec for receiving byte
/// \return received byte in LSB or <0 as error code

unsigned char CSerCom::receiveByte(int timeOut) {
    int rec = 0;
    int ret = 0;
    CTimeOut tout;

    if (isOpen()) {
        tout.SetMilliSec(timeOut);
        ret = read(m_PortFd, &rec, 1);
        while (ret != 1 && !tout.Elapse()) {
            ret = read(m_PortFd, &rec, 1);
            usleep(1000);
        }
        if (ret != 1) {
            throw string("Error during receive byte ");
        } else
            rec &= 0xff;
    } else {
        throw string("Port closed.");
    }

    return rec;
}

/**
 * Sends buffer object to serial port
 * @param buffer
 * @return  none
 */
int CSerCom::sendBuffer(CBuffer &buffer) {

    if (!isOpen()) {
        throw string("Port closed.");
    }


    size_t len = buffer.getLength();

    unsigned char *tempBuf = new unsigned char[len];

//    cout << "++++++sending buffer: "; //@TODO remove it
    for (size_t i = 0; i < len; i++) {
        tempBuf[i] = buffer.getBuffer()[i];
//        cout << (int) tempBuf[i] << "[0x" << hex << (int) tempBuf[i] << dec << "]("<<tempBuf[i]<<") | ";
    }
//    cout << endl;

    sendBuffer(tempBuf, len);
    delete[] tempBuf;
    return 0;
}


#define NO_GLOBAL_ERROR 0

int CSerCom::sendBuffer(unsigned char * Buffer, int Len) {

    int err = NO_GLOBAL_ERROR;
    int written = 0;
    int rep = 100;
    int rest = Len;

    if (!isOpen()) {
        throw string("Port closed.");
    }
    if (Len <= 0 || !Buffer) {
        throw string("Error with sending buffer");
    }

    do {

        written = write(m_PortFd, Buffer, rest);

        if (tcdrain(m_PortFd) != 0) {
//                        cout<<"tcdrain error"<<endl;
            //log->error("tcdrain error");
        }
        if (written >= 0)
            rest = Len - written;

//        cout << "rep: " << rep << ", rest: " << rest << endl;
//        sleep(1);
    } while (!err && rest > 0 && rep--);

    if (rest > 0) {

        throw string("Error during sending buffer, data sending incomplete");
    }
    return err;
}



////////////////////////////////////////////////////////////////////////
/// Flush all data from ports receive buffer
/// \param none
/// \return 0= OK, <0 error code

int CSerCom::flushReceiveBuffer(void) {
    if (!isOpen()) {
        throw string("Port closed.");
    }

    tcflush(m_PortFd, TCIFLUSH);

    return 0;
}
