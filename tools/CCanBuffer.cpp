/* 
 * File:   CCanBuffer.cpp
 * Author: jezierski
 * 
 * Created on 3 czerwiec 2013, 18:06
 */

#include "CCanBuffer.h"
#include "../can_devices/CCanConstans.h"

CCanBuffer::CCanBuffer() {
}

CCanBuffer::CCanBuffer(const CCanBuffer& orig) {
}

CCanBuffer::~CCanBuffer() {
}


void CCanBuffer::insertId(unsigned int id){
    this->id = id;
}

unsigned int CCanBuffer::frameId(){
    return id;
}

void CCanBuffer::insertCommand(unsigned char cmd){
    command = cmd;
}

unsigned char CCanBuffer::frameCommand(){
    return this->operator [](OFFSET_CMD);
}

unsigned char CCanBuffer::sourceId(){
    return this->operator [](OFFSET_CAT_ID);
}

void CCanBuffer::buildBuffer(){
    CCanBuffer buf;
    buf << (unsigned char) ID_MASTER;
    buf << (unsigned char) command;
    for (size_t i = 0; (i < this->getLength()) && (i < 6); i++){
        buf << (unsigned char) this->operator [](i);
    }
    
    this->clear();
    for (size_t i = 0; i < buf.getLength(); i++){
        this->operator <<((unsigned char) buf[i]);
    }
}

unsigned int CCanBuffer::getUID(){
    unsigned int uid;
    uid = ((this->operator [](OFFSET_DATA + 0) << 24) & 0xff000000);
    uid |= ((this->operator [](OFFSET_DATA + 1) << 16) & 0x00ff0000);
    uid |= ((this->operator [](OFFSET_DATA + 2) << 8) & 0x0000ff00);
    uid |= ((this->operator [](OFFSET_DATA + 3) << 0) & 0x000000ff);
    return uid;
}