/* 
 * File:   CFirmwareLoader.h
 * Author: jezierski
 *
 * Created on December 23, 2013, 9:30 AM
 */

#ifndef CFIRMWAREDONWLOADER_H
#define	CFIRMWAREDONWLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "CLog.h"
#include "CTools.h"
#include "CFirmwareBuffer.h"

#define OFFSET_FIRMWARE_LENGTH   0
#define OFFSET_FIRMWARE_ADDR   1
#define OFFSET_FIRMWARE_DATA     4

using namespace std;

typedef vector<unsigned char> RawData;

class CFirmwareLoader {
public:
    CFirmwareLoader();
//    CFirmwareLoader(const CFirmwareLoader& orig);
    virtual ~CFirmwareLoader();
    
    
    
    void printFileList();
    CFirmwareBuffer readFile(string filename);
private:
    CLog *log;
    
    bool checkCRC(RawData &input);
    bool checkInputData(RawData &input);
    unsigned int getAddress(RawData &input);
    CBuffer getData(RawData &input);
    RawData parseData (string &input);
};

#endif	/* CFIRMWAREDONWLOADER_H */

