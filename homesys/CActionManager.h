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
    
    void addOperation(SOperation operation);
    void makeOperation();
    void runActionManager();
    
    void assignDeviceManager(CDeviceManager *deviceManager);
private:
    CDeviceManager *deviceManager;
    mutex operationLock;
    list<SOperation> operationsList;
};

#endif	/* CACTIONMANAGER_H */

