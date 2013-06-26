/* 
 * File:   DevicesConfig.h
 * Author: jezierski
 *
 * Created on 22 czerwiec 2013, 23:03
 */



#ifndef CDEVICESCONFIG_H
#define	CDEVICESCONFIG_H
//@TODO objac uzycie funkcji configuration w try-catch
#include <string>
#include "types.h"
#include "../can_devices/CCanConstans.h"
#include "CDatabase.h"
#include <vector>
#include "CTools.h"

using namespace std;

class CDevicesConfig {
public:
    CDevicesConfig();
    //    DevicesConfig(const DevicesConfig& orig);
    virtual ~CDevicesConfig();

    void addEmptyDevice(unsigned int guid, unsigned char category, unsigned char address) {
        database->query("insert into devices VALUES('" + to_string(guid) + "', '', " + to_string((int) category) + "', '" + to_string((int) address) + "', '')");
    }

    void addDevice(SDeviceDescription device) {
        database->query("insert into devices VALUES('" + to_string(device.guid) + "', '" + to_string((int) device.luid) +  "', '" + to_string((int) device.category) + "', '" + to_string((int) device.address) + "', '"+ device.name +"')");
    }
    
    void clearDeviceAddress(unsigned char category, unsigned char address) {
        database->query("update devices set address='' where category='" + to_string((int) category) + "' and address='" + to_string((int) address) + "'");
    }

    void setDeviceName(SDeviceDescription device) {
        database->query("update devices set name='" + device.name + "' where guid='" + to_string(device.guid) + "' and category='" + to_string((int) device.category) + "' and luid='" + to_string((int) device.luid) + "'");
    }

    void updateDevicesGroup(Devices devicesList) {
        database->query("delete from devices where guid='" + to_string(devicesList[0].guid) + "' and category ='"+ to_string((int) devicesList[0].category) + "'");
        for (SDeviceDescription &device : devicesList) {
            addDevice(device);
        }
    }

//    string getDeviceName(unsigned int guid, unsigned char category, unsigned char address) {
//        vector < vector < string >> result = database->query("select name from devices where guid='" + to_string(guid) + "' and category='" + to_string((int) category) + "' and address='" + to_string((int) address) + "'");
//        //for (auto &v : result){
//        if (result.size() > 0)
//            return result[0][0];
//        else
//            return "";
//        //}
//    }

    Devices getDevices(unsigned int guid, unsigned char category) {
        vector < vector < string >> devicesList = database->query("select * from devices where guid='" + to_string(guid) + "' and category='" + to_string((int) category) + "'");
        Devices devices;
        SDeviceDescription device;
        for (vector<string> &dev : devicesList) {
            device.guid = fromString<unsigned int>(dev[0]);
            device.luid = fromString<unsigned int>(dev[1]);
            device.category = static_cast<EDeviceCategory> (fromString<unsigned int>(dev[2]));
            device.address = fromString<unsigned int>(dev[3]);
            device.name = dev[4];

            devices.push_back(device);
        }

        return devices;
    }

    void clearAddresses() {
        database->query("update devices set address = ''");
    }

    //bool isDeviceExist(unsigned int guid, unsigned char category, unsigned char address);

    static CDevicesConfig* getInstance();

private:
    static CDevicesConfig *instance;
    CDatabase *database;

};

#endif	/* DEVICESCONFIG_H */

