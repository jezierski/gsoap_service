/* 
 * File:   CFirmwareBuffer.cpp
 * Author: jezierski
 * 
 * Created on December 23, 2013, 12:26 PM
 */

#include "CFirmwareBuffer.h"

CFirmwareBuffer::CFirmwareBuffer() {
}

//CFirmwareBuffer::CFirmwareBuffer(const CFirmwareBuffer& orig) {
//}

CFirmwareBuffer::~CFirmwareBuffer() {
}

void CFirmwareBuffer::addData(unsigned int address, CBuffer& data){
    cout<<"ADR: "<<address<<", DATA: "<<endl;
    data.printBuffer();
    unsigned int currentBufSize = this->getLength();
    if (not startAddress){
        startAddress = address;
        this->clear();
    }else{
        for (size_t i = 0; i < (address - startAddress - currentBufSize); i++){
            this->operator <<((unsigned char) 0xff);
        }
    }
    this->operator <<(data);
}

unsigned int CFirmwareBuffer::getStartAddress(){
    offset = 0;
    return startAddress;
}


CBuffer CFirmwareBuffer::getDataBlock(unsigned char length){
    CBuffer buf = this->subBuffer(offset, length);
    offset += length;
    return buf;
}

unsigned char CFirmwareBuffer::getReadingProgress(){
    cout<<"offset: "<<offset<<", len: " <<this->getLength()<<", prog: " <<offset * 100 / this->getLength()<<endl;
    return (offset * 100 / this->getLength());
}
