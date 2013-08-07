/* 
 * File:   CTimer.h
 * Author: jezierski
 *
 * Created on August 7, 2013, 5:37 PM
 */

#ifndef CTIMER_H
#define	CTIMER_H

#include <map>
#include <list>
#include <mutex>
#include "COperation.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "../tools/CTools.h"
#include "CDeviceManager.h"

using namespace std;

class CTimer {
public:
    CTimer();
//    CTimer(const CTimer& orig);
    virtual ~CTimer();
    
    void run();
    void addTimerSet(long long set);
    void resetTimerSet();
    
    Signal1<long long> timerEvent;
private:
    list<long long> timerSets;

};

#endif	/* CTIMER_H */

