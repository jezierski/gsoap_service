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
    void insertCommand(unsigned char cmd);
    unsigned int frameId();
    unsigned char frameCommand();
    void buildBuffer();
private:
    unsigned int id = 0;
    unsigned char command;
};

#endif	/* CCANBUFFER_H */

