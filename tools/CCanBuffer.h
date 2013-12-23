/* 
 * File:   CCanBuffer.h
 * Author: jezierski
 *
 * Created on 3 czerwiec 2013, 18:06
 */

#ifndef CCANBUFFER_H
#define	CCANBUFFER_H

#include "CBuffer.h"

class CCanBuffer : public CBuffer{
public:
    CCanBuffer();
//    CCanBuffer(const CCanBuffer& orig);
    virtual ~CCanBuffer();
    
    void insertId(unsigned int id);
    void insertCommand(unsigned char cmd);
    void insertDestinationAddress(unsigned char adr);
    void insertFlashAddress(unsigned int address);
    void insertBootCommand(unsigned char command);
    void insertBootControlBits(unsigned char bits);
    unsigned int frameId();
    unsigned char frameCommand();
    unsigned char sourceId();
    unsigned char sourceAddress();
    
    unsigned int getGUID();
    unsigned char getNmbDevices();
    
    unsigned char getSensorCommand();
    vector<unsigned char> getSensorParams();
    
    void buildBuffer();
    void buildBootBuffer();
    
private:
    unsigned int flashAddress = 0;
    unsigned char bootCommand = 0;
    unsigned char bootControlBits = 0;
    
    unsigned int id = 0;
    unsigned char command;
    unsigned char destAddress = 0;
};

#endif	/* CCANBUFFER_H */

