

#ifndef CBUFFER_H
#define	CBUFFER_H

#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CBuffer {
public:
    CBuffer();
    virtual ~CBuffer();
    CBuffer& operator <<(int num);

    CBuffer& operator <<(short num);
    CBuffer& operator <<(unsigned int num);
    CBuffer& operator <<(unsigned char num);
    CBuffer& operator <<(string str);
    CBuffer& operator <<(wstring str);
    CBuffer& operator <<(CBuffer &buffer);

    unsigned char operator[](unsigned int index);
    void clear();

    operator string();

    unsigned char getCommand();
    vector<unsigned char> &getBuffer();
    unsigned char getBuffer(unsigned char index);
    CBuffer subBuffer(unsigned int start, unsigned int length);
    size_t getLength();
    bool isReady();
    void setReady();
    void printBuffer();
    bool operator ==(CBuffer &buf);
    
    bool isACK();
    bool isNoData();
    unsigned char getErrorCode();
private:
    vector<unsigned char> buffer;
    bool ready;
    unsigned char len;
    unsigned char command;
    int bufferPointer;
    CBuffer(unsigned char command, unsigned char *data, unsigned char length);

    //    void operator =(CBuffer &buf);

};
#endif	

