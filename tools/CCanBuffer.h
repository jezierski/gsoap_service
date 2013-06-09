/* 
 * File:   CCanBuffer.h
 * Author: jezierski
 *
 * Created on 3 czerwiec 2013, 18:06
 */

#ifndef CCANBUFFER_H
#define	CCANBUFFER_H

#include "../tools/CBuffer.h"

class CCanBuffer : public CBuffer{
public:
    CCanBuffer();
    CCanBuffer(const CCanBuffer& orig);
    virtual ~CCanBuffer();
    
    void insertId(unsigned int id);
    unsigned int frameId();
private:
    unsigned int id = 0;
};

#endif	/* CCANBUFFER_H */

