/* 
 * File:   CParamsConverter.h
 * Author: jezierski
 *
 * Created on September 25, 2013, 9:19 PM
 */

#ifndef CPARAMSCONVERTER_H
#define	CPARAMSCONVERTER_H


#include "types.h"
#include "../can_devices/CCanConstans.h"
#include "../can_devices/CCanRGBActor.h"
#include <map>

using namespace std;

class CParamsConverter {
public:
    CParamsConverter();
    //    CParamsConverter(const CParamsConverter& orig);
    virtual ~CParamsConverter();

    Blob use(int category, int command, long long  params);


    static CParamsConverter * getInstance();

private:
    typedef
    Blob(CParamsConverter::*convert)(long long);
//    map<int, convert> commandsMap;
    map<int, map<int, convert>> convertionsMap;
//    map<int, convert> commandsMap;
//    map<int, commandsMap> convertionsMap;

    void initConvertionsMap();

    Blob singleRGBvalueSet(long long params);
    Blob allRGBvaluesSet(long long params);

    static CParamsConverter *instance;
};

#endif	/* CPARAMSCONVERTER_H */

