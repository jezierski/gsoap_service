/* 
 * File:   CFirmwareBuffer.cpp
 * Author: jezierski
 * 
 * Created on December 23, 2013, 12:26 PM
 */

#include "CFirmwareBuffer.h"

CFirmwareBuffer::CFirmwareBuffer() {
}

CFirmwareBuffer::CFirmwareBuffer(const CBuffer& orig) : CBuffer(orig) {
//    cout<<"KONSTRUKTOR KOP"<<endl;
    
}

CFirmwareBuffer::~CFirmwareBuffer() {
}

void CFirmwareBuffer::addData(unsigned int address, CBuffer& data) {
    cout << "ADR: " << address << ", DATA: " << endl;
    data.printBuffer();
    unsigned int currentBufSize = this->getLength();
    if (not startAddress) {
        startAddress = address;
        this->clear();
    } else {
        for (size_t i = 0; i < (address - startAddress - currentBufSize); i++) {
            this->operator <<((unsigned char) 0xff);
        }
    }
    this->operator <<(data);
}

void CFirmwareBuffer::resetOffset(){
    offset = 0;
}

//unsigned int CFirmwareBuffer::getStartAddress() {
//    offset = 0;
//    return startAddress;
//}

//CFirmwareBuffer CFirmwareBuffer::getDataBlock(unsigned char length) {
//    CFirmwareBuffer buf = this->subBuffer(offset, length);
//    buf.setOffsetAddress(startAddress + offset);
//    offset += length;
//    return buf;
//}

CFirmwareBuffer CFirmwareBuffer::getNotNullDataBlock(unsigned char length) {
    CFirmwareBuffer buf;
    do {
        buf = this->subBuffer(offset, length);
        offset += length;
//        cout<<"taking subbufer"<<endl;
    } while (buf.isNullDataBuffer() && buf.getLength());
    buf.setOffsetAddress(startAddress + offset - length);
    return buf;
}

unsigned char CFirmwareBuffer::getReadingProgress() {
    cout << "offset: " << offset << ", len: " << this->getLength() << ", prog: " << offset * 100 / this->getLength() << endl;
    return (offset * 100 / this->getLength());
}

unsigned int CFirmwareBuffer::getDataBlockAddress() {
    return offsetAddress;
}

void CFirmwareBuffer::setOffsetAddress(unsigned int offset) {
    this->offsetAddress = offset;
}

bool CFirmwareBuffer::isNullDataBuffer() {
    for (size_t i = 0; i < this->getLength(); i++) {
        if (this->operator [](i) != NULL_DATA) {
            return false;
        }
    }
    return true;
}