/* 
 * File:   CFirmwareBuffer.cpp
 * Author: jezierski
 * 
 * Created on December 23, 2013, 12:26 PM
 */

#include <map>

#include "CFirmwareBuffer.h"

CFirmwareBuffer::CFirmwareBuffer() {
}

CFirmwareBuffer::CFirmwareBuffer(const CBuffer& orig) : CBuffer(orig) {
    //    cout<<"KONSTRUKTOR KOP"<<endl;

}

CFirmwareBuffer::~CFirmwareBuffer() {
}

void CFirmwareBuffer::addData(unsigned int address, CBuffer& data) {
//    cout << "addData ADR: " << address << ", DATA: " << endl;
//    data.printBuffer();
    unsigned int currentBufSize = this->getLength();
    if (not startAddress) {
        startAddress = address;
        this->clear();
    } else {
        for (size_t i = 0; i < (address - startAddress - currentBufSize); i++) {
            this->operator <<((unsigned char) NULL_DATA);
        }
    }
    this->operator <<(data);
}

void CFirmwareBuffer::addExData(unsigned int address, CBuffer& data) {
//    cout << "addExData ADR: " << address << ", startAddr: "<<startAddress<<", DATA: " << endl;
//    data.printBuffer();
    unsigned int currentBufSize = this->getLength();
    if (not startAddress) {
        startAddress = address;
        this->clear();
    } else {
        for (size_t i = 0; i < (address - startAddress - currentBufSize); i++) {
            this->operator <<((unsigned char) NULL_EX_DATA);
        }
    }
    this->operator <<(data);
}

void CFirmwareBuffer::addExBufferData(unsigned int address, CBuffer &buffer) {

    ExBufMap::const_iterator itr;
    for (itr = extendedBuffers.begin(); itr != extendedBuffers.end(); ++itr) {
        if ((itr->first & 0xff0000) == (address & 0xff0000)) {
            extendedBuffers[itr->first].addExData(address, buffer);
            return;
        }
    }
//    cout << "create new EX BUF [" << address << "]" << endl;
    extendedBuffers[address] = buffer;
    extendedBuffers[address].startAddress = address;

}

unsigned char CFirmwareBuffer::getExBufferQnty() {
    return extendedBuffers.size();
}

CFirmwareBuffer CFirmwareBuffer::getExBuffer(unsigned char id) {
    ExBufMap::iterator itr;
    unsigned char index = 0;
    for (itr = extendedBuffers.begin(); itr != extendedBuffers.end(); ++itr) {
        if (id == index){
            return extendedBuffers[itr->first];
        }else{
            index++;
        }
    }
    CFirmwareBuffer dummy;
    return dummy;
}

void CFirmwareBuffer::resetOffset() {
    offset = 0;
}

CFirmwareBuffer CFirmwareBuffer::getNotNullDataBlock(unsigned char length) {
    CFirmwareBuffer buf;
    do {
        buf = this->subBuffer(offset, length);
        offset += buf.getLength();

    } while (buf.isNullDataBuffer() && buf.getLength());

    if (buf.getLength() > 0 && buf.getLength() < 8) {
        length = buf.getLength();
        for (size_t i = length; i < 8; i++) {
            buf << (unsigned char) NULL_DATA;
        }
    }
    buf.setOffsetAddress(startAddress + offset - length);

    return buf;
}

CFirmwareBuffer CFirmwareBuffer::getDataBlock(unsigned char length) {
    CFirmwareBuffer buf;
    do {
        buf = this->subBuffer(offset, length);
        offset += buf.getLength();

    } while (buf.isNullDataBuffer() && buf.getLength());

    if (buf.getLength() > 0 && buf.getLength() < 8) {
        length = buf.getLength();
    }
    buf.setOffsetAddress(startAddress + offset - length);

    return buf;
}

unsigned char CFirmwareBuffer::getReadingProgress() {
    //    cout << "offset: " << offset << ", len: " << this->getLength() << ", prog: " << offset * 100 / this->getLength() << endl;
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
