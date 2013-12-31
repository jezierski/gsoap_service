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
#define NULL_EX_DATA       0x00

class CFirmwareBuffer : public CBuffer{
public:
    CFirmwareBuffer();
    CFirmwareBuffer(const CBuffer& orig);
    virtual ~CFirmwareBuffer();
    
    void addData(unsigned int address, CBuffer &data);
    void addExData(unsigned int address, CBuffer& data);
    void resetOffset();
    CFirmwareBuffer getNotNullDataBlock(unsigned char length = 8);
    CFirmwareBuffer getDataBlock(unsigned char length = 8);
    unsigned char getReadingProgress();
    unsigned int getDataBlockAddress();
    void setOffsetAddress(unsigned int offset);
    void addExBufferData(unsigned int address, CBuffer &buffer);
    unsigned char getExBufferQnty();
    CFirmwareBuffer getExBuffer(unsigned char id);
    
private:
    bool isNullDataBuffer();
    unsigned int startAddress = 0;
    unsigned int offset = 0;
    unsigned int offsetAddress = 0;
    typedef map<int, CFirmwareBuffer> ExBufMap;
    
    ExBufMap extendedBuffers;
};

#endif	/* CFIRMWAREBUFFER_H */

