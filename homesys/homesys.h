#ifndef HOMESYS_H
#define	HOMESYS_H

#include "CSoapServer.h"
#include "../webservice/homesys.nsmap"
#include <iostream>

using namespace std;

class CApplication{
public:
    CApplication();
    virtual ~CApplication();
    
    void run();
};
#endif
