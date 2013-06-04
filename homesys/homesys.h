#ifndef HOMESYS_H
#define	HOMESYS_H

#include <iostream>

#include "../webservice/homesys.nsmap"
#include "CSoapServer.h"
#include "../can232/CCan232.h"

using namespace std;

class CApplication{
public:
    CApplication();
    virtual ~CApplication();
    
    void run();
};
#endif
