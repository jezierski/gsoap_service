/* 
 * File:   CActionManager.h
 * Author: jezierski
 *
 * Created on September 24, 2013, 9:00 PM
 */

#ifndef CACTIONMANAGER_H
#define	CACTIONMANAGER_H


#include <map>
#include <list>
#include <mutex>
#include "COperation.h"
#include "../tools/CLog.h"
#include "../tools/types.h"
#include "../tools/CTools.h"
#include "CDeviceManager.h"

using namespace std;

class CActionManager {
public:
    CActionManager();
//    CActionManager(const CActionManager& orig);
    virtual ~CActionManager();
    
    void addAction(SAction action);
    void makeAction();
    void runActionManager();
    
    void assignDeviceManager(CDeviceManager *deviceManager);
private:
    CDeviceManager *deviceManager;
    mutex actionLock;
    list<SAction> actionList;
};

#endif	/* CACTIONMANAGER_H */

