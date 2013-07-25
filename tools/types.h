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



typedef struct DeviceDescriptor {
    unsigned int guid;
    unsigned char luid;
    EDeviceCategory category;
    unsigned char address;
    string name;

    bool operator<(const DeviceDescriptor & n) const {
        if (this->guid == n.guid) {
            if (static_cast<int> (this->category) == static_cast<int> (n.category)) {
                return this->luid < n.luid;
            }else{
                return static_cast<int> (this->category) < static_cast<int> (n.category);
            }
        } else {
            return this->guid < n.guid;
        }
    }
} SDeviceDescription;

typedef vector<SDeviceDescription> Devices;

typedef map<string, CBlob> Blob;

typedef vector<unsigned char> Params;

typedef unsigned char Command;

#endif	/* TYPES_H */

