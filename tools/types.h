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

using namespace std;

typedef struct SDeviceDescription{
    unsigned int guid;
    unsigned char luid;
    EDeviceCategory category;
    unsigned char address;
    string name;
}SDeviceDescription;

typedef vector<SDeviceDescription> Devices;


#endif	/* TYPES_H */

