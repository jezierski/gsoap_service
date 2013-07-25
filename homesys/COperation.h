/* 
 * File:   COperation.h
 * Author: jezierski
 *
 * Created on 20 lipiec 2013, 21:36
 */

#ifndef COPERATION_H
#define	COPERATION_H
#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include "../tools/rapidxml.hpp"
#include "../tools/types.h"
#include "../tools/CLog.h"


using namespace std;
using namespace rapidxml;

enum class ECondition {
    Equal = 1,
            Less = 2,
            More = 3,
};

typedef struct {
    SDeviceDescription device;
    Command command;
    Params params;
    bool status;
} SAction;

typedef struct {
    SDeviceDescription device;
    Command command;
    ECondition condition;
    Params params;
} SDeviceCondition;

typedef struct {
    ECondition condition;
    time_t time;
} STimeCondition;

typedef struct {
    list<SDeviceCondition>deviceConditions;
    list<STimeCondition>timeConditions;
    SAction action;
} SOperation;

class COperation {
public:
    COperation();
    //    COperation(const COperation& orig);
    virtual ~COperation();

    void loadOperations();
private:

    string readFile(string fileName);
    list<SOperation>operations;
    
    typedef
    void (COperation::*nodeFunctor)(const xml_node<>* node, SOperation&);
    map<string, nodeFunctor> nodeFunctors;
    
    typedef
    void (COperation::*conditionSensorAttributeFunctor)(string value, SDeviceCondition&);
    map<string, conditionSensorAttributeFunctor> sensorAttributeFunctors;

    typedef
    void (COperation::*conditionActorAttributeFunctor)(string value, SAction&);
    map<string, conditionActorAttributeFunctor> actorAttributeFunctors;
    
    typedef
    void (COperation::*conditionTimeAttributeFunctor)(string value, STimeCondition&);
    map<string, conditionTimeAttributeFunctor> timeAttributeFunctors;
    
    void initNodeFunctors();
    void initSensorAttributeFunctor();
    void initActorAttributeFunctor();
    void initTimeAttributeFunctor();

   
    void parseNode(string nodeName, const xml_node<>* node, SOperation&);
    void parseSensorAttribute(string attributeName, string value, SDeviceCondition&);
    void parseActorAttribute(string attributeName, string value, SAction&);
    void parseTimeAttribute(string attributeName, string value, STimeCondition& condition);
    
    void nodeOperation(const xml_node<>* node, SOperation&);
    void nodeCondition(const xml_node<>* node, SOperation&);
    void nodeAction(const xml_node<>* node, SOperation&);
    void nodeSensor(const xml_node<>* node, SOperation&);
    void nodeActor(const xml_node<>* node, SOperation&);
    void nodeTime(const xml_node<>* node, SOperation&);
    
    SDeviceCondition parseSensor(const xml_node<>* node);
    SAction parseActor(const xml_node<>* node);
    STimeCondition parseTime(const xml_node<>* node);

    
    void parseGUID(string value, SDeviceCondition&);
    void parseLUID(string value, SDeviceCondition&);
    void parseCategory(string value, SDeviceCondition&);
    void parseCommand(string value, SDeviceCondition&);
    void parseCondition(string value, SDeviceCondition&);
    void parseParams(string value, SDeviceCondition&);
    
    void parseGUID(string value, SAction&);
    void parseLUID(string value, SAction&);
    void parseCategory(string value, SAction&);
    void parseCommand(string value, SAction&);
    void parseParams(string value, SAction&);
    
    void parseCondition(string value, STimeCondition&);
    void parseParams(string value, STimeCondition&);
    
    void parseParams(string, Params&);
    void addOperation(SOperation operation);
    void clearOperation(SOperation &operation);
    CLog *log;
};

#endif	/* COPERATION_H */

