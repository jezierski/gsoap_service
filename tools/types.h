/* 
 * File:   types.h
 * Author: jezierski
 *
 * Created on 24 czerwiec 2013, 22:48
 */

#ifndef TYPES_H
#define	TYPES_H

#include "../can_devices/CCanConstans.h"
#include <string>
#include <vector>
#include "CBlob.h"

using namespace std;

typedef struct{
    unsigned int guid;
    unsigned char luid;
    EDeviceCategory category;
    unsigned char address;
    string name;
} SDeviceDescription ;

typedef vector<SDeviceDescription> Devices;

typedef map<string, CBlob> Blob;

typedef vector<unsigned char> Params;

typedef unsigned char Command;

#endif	/* TYPES_H */

