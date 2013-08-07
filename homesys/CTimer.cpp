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
    long long timer;
    while(1){
        timer = getCurrentDayTime();
        for (long long time : timerSets){
            if (time == timer){
                timerEvent(time);
            }
        }
        msleep(300);
    }
}

void CTimer::addTimerSet(long long set) {
    timerSets.push_back(set);
    timerSets.sort();
}

void CTimer::resetTimerSet() {
    timerSets.clear();
}
