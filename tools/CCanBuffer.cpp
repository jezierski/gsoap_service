/* 
 * File:   CCanBuffer.cpp
 * Author: jezierski
 * 
 * Created on 3 czerwiec 2013, 18:06
 */

#include "CCanBuffer.h"

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