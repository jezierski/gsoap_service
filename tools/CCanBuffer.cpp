/* 
 * File:   CCanBuffer.cpp
 * Author: jezierski
 * 
 * Created on 3 czerwiec 2013, 18:06
 */

#include "CCanBuffer.h"
#include "can_devices/CCanConstans.h"

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
    return command;
}

void CCanBuffer::buildBuffer(){
    CCanBuffer buf;
    buf << (unsigned char) ID_MASTER;
    buf << (unsigned char) frameCommand();
    for (size_t i = 0; (i < this->getLength()) && (i < 6); i++){
        buf << (unsigned char) this->operator [](i);
    }
    
    this->clear();
    for (size_t i = 0; i < buf.getLength(); i++){
        this->operator <<((unsigned char) buf[i]);
    }
}