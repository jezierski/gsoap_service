/* 
 * File:   CCanSimpleSwitch.h
 * Author: jezierski
 *
 * Created on 10 czerwiec 2013, 20:55
 */

#ifndef CCANSIMPLESWITCHACTOR_H
#define	CCANSIMPLESWITCHACTOR_H

#include "../homesys/CDevice.h"
#include "../tools/CCanBuffer.h"
#include "CCanConstans.h"






using namespace std;

class CCanSimpleSwitchActor : public CDevice {
public:
    CCanSimpleSwitchActor();
//    CCanSimpleSwitch(const CCanSimpleSwitch& orig);
    virtual ~CCanSimpleSwitchActor();
private:

};

#endif	/* CCANSIMPLESWITCH_H */

