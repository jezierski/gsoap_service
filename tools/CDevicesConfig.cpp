/* 
 * File:   DevicesConfig.cpp
 * Author: jezierski
 * 
 * Created on 22 czerwiec 2013, 23:03
 */

#include "CDevicesConfig.h"

CDevicesConfig::CDevicesConfig() {
    database = CDatabase::getInstance();
}

//DevicesConfig::DevicesConfig(const DevicesConfig& orig) {
//}

CDevicesConfig::~CDevicesConfig() {
}

CDevicesConfig* CDevicesConfig::getInstance() {
    if (!instance)
        instance = new CDevicesConfig();

    return instance;

}

CDevicesConfig* CDevicesConfig::instance = NULL;
