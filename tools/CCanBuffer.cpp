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

CCanBuffer::CCanBuffer(const CBuffer& orig) : CBuffer(orig) {
}

CCanBuffer::~CCanBuffer() {
}

void CCanBuffer::insertId(unsigned int id) {
    this->id = id;
}

unsigned int CCanBuffer::frameId() {
    return id;
}

void CCanBuffer::insertCommand(unsigned char cmd) {
    command = cmd;
}

void CCanBuffer::insertFlashAddress(unsigned int address) {
    this->flashAddress = address & 0xffffff;
}

void CCanBuffer::insertBootCommand(unsigned char command) {
    this->bootCommand = command & 0x0f;
}

void CCanBuffer::insertBootControlBits(unsigned char bits) {
    this->bootControlBits = bits & 0x1f;
}

void CCanBuffer::insertDestinationAddress(unsigned char adr) {
    destAddress = adr;
}

unsigned char CCanBuffer::frameCommand() {
    return this->operator [](OFFSET_CMD);
}

unsigned char CCanBuffer::sourceId() {
    return this->operator [](OFFSET_CAT_ID);
}

unsigned char CCanBuffer::sourceAddress() {
    return this->operator [](OFFSET_SRC_ADDR);
}

unsigned char CCanBuffer::getSensorCommand() {
    return this->operator [](OFFSET_SENSOR_RESPONSE_COMMAND);
}

vector<unsigned char> CCanBuffer::getSensorParams() {
    vector<unsigned char> params;
    params.insert(params.begin(), this->getBuffer().begin() + OFFSET_SENSOR_RESPONSE_DATA, this->getBuffer().end());
    return params;
}

void CCanBuffer::buildBuffer() {
    CCanBuffer buf;
    buf << (unsigned char) ID_MASTER;
    buf << (unsigned char) command;
    if (destAddress) {
        buf << (unsigned char) destAddress;
        for (size_t i = 0; (i < this->getLength()) && (i < 5); i++) {
            buf << (unsigned char) this->operator [](i);
        }
    } else {

        for (size_t i = 0; (i < this->getLength()) && (i < 6); i++) {
            buf << (unsigned char) this->operator [](i);
        }
    }
    this->clear();
    for (size_t i = 0; i < buf.getLength(); i++) {
        this->operator <<((unsigned char) buf[i]);
    }
}

void CCanBuffer::buildBootBuffer() {
    CCanBuffer buf;
    buf << (unsigned char) ((flashAddress >> 0) & 0xff);
    buf << (unsigned char) ((flashAddress >> 8) & 0xff);
    buf << (unsigned char) ((flashAddress >> 16) & 0xff);
    buf << (unsigned char) 0;
    buf << (unsigned char) bootControlBits;
    buf << (unsigned char) bootCommand;
    buf << (unsigned char) 0;
    buf << (unsigned char) 0;

    this->clear();
    for (size_t i = 0; i < buf.getLength(); i++) {
        this->operator <<((unsigned char) buf[i]);
    }
    bootControlBits = bootCommand = flashAddress = 0;
}

unsigned int CCanBuffer::getGUID() {
    unsigned int guid;
    guid = ((this->operator [](OFFSET_DATA + 0) << 24) & 0xff000000);
    guid |= ((this->operator [](OFFSET_DATA + 1) << 16) & 0x00ff0000);
    guid |= ((this->operator [](OFFSET_DATA + 2) << 8) & 0x0000ff00);
    guid |= ((this->operator [](OFFSET_DATA + 3) << 0) & 0x000000ff);
    return guid;
}

int CCanBuffer::getBootGUID() {
    int guid;
    guid = ((this->operator [](0) << 24) & 0xff000000);
    guid |= ((this->operator [](1) << 16) & 0x00ff0000);
    guid |= ((this->operator [](2) << 8) & 0x0000ff00);
    guid |= ((this->operator [](3) << 0) & 0x000000ff);
    return guid;
}

unsigned int CCanBuffer::getBootCRC(){
    this->printBuffer();
    unsigned int crc = this->operator[](0);
    crc |= (this->operator[](1) << 8);
    return crc;
}

unsigned char CCanBuffer::getNmbDevices() {
    return this->operator [](OFFSET_DATA + 4);
}