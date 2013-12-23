/* 
 * File:   CFirmwareBuffer.h
 * Author: jezierski
 *
 * Created on December 23, 2013, 12:26 PM
 */

#ifndef CFIRMWAREBUFFER_H
#define	CFIRMWAREBUFFER_H

#include "CBuffer.h"

class CFirmwareBuffer : public CBuffer{
public:
    CFirmwareBuffer();
//    CFirmwareBuffer(const CFirmwareBuffer& orig);
    virtual ~CFirmwareBuffer();
    
    void addData(unsigned int address, CBuffer &data);
    unsigned int getStartAddress();
    CBuffer getDataBlock(unsigned char length = 8);
    unsigned char getReadingProgress();
    
private:
    unsigned int startAddress = 0;
    unsigned int offset = 0;
};

#endif	/* CFIRMWAREBUFFER_H */

