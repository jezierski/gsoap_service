/* 
 * File:   CBlob.cpp
 * Author: jezierski
 * 
 * Created on 29 czerwiec 2013, 10:17
 */

#include "CBlob.h"

CBlob::CBlob() {
    a = init++;
}

//CBlob::CBlob(const CBlob& orig) {
//}

CBlob::~CBlob() {
}
int CBlob::init = 0;

