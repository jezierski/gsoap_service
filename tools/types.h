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
#include <list>
#include "CBlob.h"
#include "CCanBuffer.h"


#define BLOB_ACTION_PARAMETER        "param"
#define BLOB_DEVICE_NAME             "name"
#define BLOB_RGB_CHANNEL             "rgb_ch"
#define BLOB_RGB_ALL                 "rgb_all"


using namespace std;



typedef struct DeviceDescriptor {
    unsigned int guid = 0;
    unsigned char luid = 0;
    EDeviceCategory category = EDeviceCategory::OTHER;
    unsigned char address = 0;
    string name = "";

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

typedef vector<CCanBuffer> CanBuffers;

typedef unsigned char Command;

typedef map<unsigned char, Params>  DeviceParams;

typedef map<SDeviceDescription, DeviceParams> DeviceState;

typedef struct {
    SDeviceDescription device;
    Command command;
    Blob params;
} SAction;

typedef struct{
    SAction action;
    SAction reaction;
} SChain;

enum class ECondition {
    Equal = 1,
            Less = 2,
            More = 3,
            LessOrEqual = 4,
            MoreOrEqual = 5
};

typedef struct {
    SDeviceDescription device;
    Command command;
    ECondition condition;
    Params params;
} SDeviceCondition;

typedef struct {
    ECondition condition;
    long long time;
} STimeCondition;

typedef struct {
    list<SDeviceCondition>deviceConditions;
    list<STimeCondition>timeConditions;
    SAction action;
} SOperation;


#endif	/* TYPES_H */

