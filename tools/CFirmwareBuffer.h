/* 
 * File:   CFirmwareBuffer.h
 * Author: jezierski
 *
 * Created on December 23, 2013, 12:26 PM
 */

#ifndef CFIRMWAREBUFFER_H
#define	CFIRMWAREBUFFER_H

#include "CBuffer.h"

#define NULL_DATA       0xff

class CFirmwareBuffer : public CBuffer{
public:
    CFirmwareBuffer();
    CFirmwareBuffer(const CBuffer& orig);
    virtual ~CFirmwareBuffer();
    
    void addData(unsigned int address, CBuffer &data);
//    unsigned int getStartAddress();
//    CFirmwareBuffer getDataBlock(unsigned char length = 8);
    void resetOffset();
    CFirmwareBuffer getNotNullDataBlock(unsigned char length = 8);
    unsigned char getReadingProgress();
    unsigned int getDataBlockAddress();
    void setOffsetAddress(unsigned int offset);
    
    
private:
    bool isNullDataBuffer();
    unsigned int startAddress = 0;
    unsigned int offset = 0;
    unsigned int offsetAddress = 0;
};

#endif	/* CFIRMWAREBUFFER_H */

