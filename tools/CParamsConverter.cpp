/* 
 * File:   CParamsConverter.cpp
 * Author: jezierski
 * 
 * Created on September 25, 2013, 9:19 PM
 */

#include "CParamsConverter.h"

CParamsConverter::CParamsConverter() {
    initConvertionsMap();
}

//CParamsConverter::CParamsConverter(const CParamsConverter& orig) {
//}

CParamsConverter::~CParamsConverter() {
}

CParamsConverter *CParamsConverter::instance = NULL;


CParamsConverter* CParamsConverter::getInstance() {
    if (!instance)
        instance = new CParamsConverter();
    return instance;

}

void CParamsConverter::initConvertionsMap() {
    convertionsMap[static_cast<int> (EDeviceCategory::A_RGB_DRIVER)][ACTION_SET_CHANNEL_RED] = &CParamsConverter::singleRGBvalueSet;
    convertionsMap[static_cast<int> (EDeviceCategory::A_RGB_DRIVER)][ACTION_SET_CHANNEL_GREEN] = &CParamsConverter::singleRGBvalueSet;
    convertionsMap[static_cast<int> (EDeviceCategory::A_RGB_DRIVER)][ACTION_SET_CHANNEL_BLUE] = &CParamsConverter::singleRGBvalueSet;
    convertionsMap[static_cast<int> (EDeviceCategory::A_RGB_DRIVER)][ACTION_SET_CHANNEL_ALL] = &CParamsConverter::allRGBvaluesSet;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_SET_PWM] = &CParamsConverter::setPWM;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_SET_PWM_ALL_THE_SAME] = &CParamsConverter::setPWM;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_PWM_UP] = &CParamsConverter::changePWM;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_PWM_DOWN] = &CParamsConverter::changePWM;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_PWM_UP_ALL] = &CParamsConverter::changePWM;
    convertionsMap[static_cast<int> (EDeviceCategory::A_PWM_DRIVER)][ACTION_PWM_DOWN_ALL] = &CParamsConverter::changePWM;
}

Blob CParamsConverter::singleRGBvalueSet(LONG64 params) {
    Blob b;
    unsigned int param = static_cast<unsigned int>(params);
    b[BLOB_RGB_CHANNEL].put<unsigned int>(param);
    return b;
}

Blob CParamsConverter::allRGBvaluesSet(LONG64 params) {
    Blob b;
    vector<unsigned int > rgbVals;
    rgbVals.push_back(static_cast<unsigned int> ((params >> 24) & 0xfff));
    rgbVals.push_back(static_cast<unsigned int> ((params >> 12) & 0xfff));
    rgbVals.push_back(static_cast<unsigned int> ((params >> 0) & 0xfff));
    b[BLOB_RGB_ALL].put < vector<unsigned int >> (rgbVals);

    return b;
}

Blob CParamsConverter::setPWM(LONG64 params) {
    Blob b;
    unsigned char param = static_cast<unsigned char>(params);
    b[BLOB_PWM_VALUE].put<unsigned char>(param);
    return b;
}


Blob CParamsConverter::changePWM(LONG64 params) {
    Blob b;
    unsigned char param = static_cast<unsigned char>(params);
    b[BLOB_PWM_CHANGE].put<unsigned char>(param);
    return b;
}

Blob CParamsConverter::use(int category, int command, LONG64 params) {
    if (convertionsMap.find(category) != convertionsMap.end()) {
        if (convertionsMap[category].find(command) != convertionsMap[category].end()) {
            return (this->*convertionsMap[category][command])(params);
        }
    }
    Params p;
    for (int i = 8; i > 0; i--) {
        p.push_back(params & 0xff);
        params >>= 8;
    }
    Blob b;
    b[BLOB_ACTION_PARAMETER].put<Params>(p);
    return b;
}