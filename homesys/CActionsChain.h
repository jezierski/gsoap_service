/* 
 * File:   CActionsChain.h
 * Author: jezierski
 *
 * Created on August 8, 2013, 7:27 PM
 */

#ifndef CACTIONSCHAIN_H
#define	CACTIONSCHAIN_H

#include <list>
#include <string>
#include <fstream>
#include <cstring>
#include "../tools/rapidxml.hpp"
#include "../tools/types.h"
#include "../tools/CLog.h"
#include "../tools/CTools.h"


using namespace std;
using namespace rapidxml;




class CActionsChain {
public:
    CActionsChain();
//    CActionsChain(const CActionsChain& orig);
    virtual ~CActionsChain();
    
    void loadActionsChain();
    
    bool isChainExist(SAction &action);
private:

    string readFile(string fileName);
    list<SChain>chains;
    
    typedef
    void (CActionsChain::*nodeFunctor)(const xml_node<>* node, SChain&);
    map<string, nodeFunctor> nodeFunctors;
    
    typedef
    void (CActionsChain::*actionAttributeFunctor)(string value, SAction&);
    map<string, actionAttributeFunctor> actionAttributeFunctors;
    
    void initNodeFunctors();
    void initActionAttributeFunctor();

   
    void parseNode(string nodeName, const xml_node<>* node, SChain&);
    void parseActionAttribute(string attributeName, string value, SAction&);
   
    
    void nodeAction(const xml_node<>* node, SChain &chain);
    void nodeReaction(const xml_node<>* node, SChain &chain);
    void nodeChain(const xml_node<>* node, SChain &chain);
  
    SAction parseAction(const xml_node<>* node);
    SAction parseReaction(const xml_node<>* node);

    
    void parseGUID(string value, SAction&);
    void parseLUID(string value, SAction&);
    void parseCategory(string value, SAction&);
    void parseCommand(string value, SAction&);
    void parseParams(string value, SAction&);
    
    void parseParams(string, Params&);
    
    void addChain(SChain chain);
    void clearChain(SChain &chain);
    
    bool compareParams(Params, Params);
    
    CLog *log;
    
};

#endif	/* CACTIONSCHAIN_H */

