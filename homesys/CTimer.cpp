/* 
 * File:   CTimer.cpp
 * Author: jezierski
 * 
 * Created on August 7, 2013, 5:37 PM
 */

#include "CTimer.h"

CTimer::CTimer() {
}

//CTimer::CTimer(const CTimer& orig) {
//}

CTimer::~CTimer() {
}

void CTimer::run() {
    LONG64 timer;
    while(1){
        timer = getCurrentDayTime();
        for (LONG64 time : timerSets){
            if (time == timer){
                timerEvent(time);
            }
        }
        msleep(300);
    }
}

void CTimer::addTimerSet(LONG64 set) {
    timerSets.push_back(set);
    timerSets.sort();
}

void CTimer::resetTimerSet() {
    timerSets.clear();
}
