/* 
 * File:   CSoapServer.cpp
 * Author: Jezierski
 * 
 * Created on 18 marzec 2013, 21:18
 */

#include "CSoapServer.h"

CSoapServer::CSoapServer() {
}

CSoapServer::CSoapServer(const CSoapServer& orig) {
}

CSoapServer::~CSoapServer() {
}

int CSoapServer::getCurrentTime(string& currentTime) {
    time_t rawtime;
    time(&rawtime);
    string strTime(ctime (&rawtime));
    currentTime = strTime;
    return SOAP_OK;
}

int CSoapServer::getValue(string id, string &result){
    result = "Text etnered: " + id;
    return SOAP_OK;
}

int CSoapServer::switchPort(string pinNo, string &result){
    if (pinNo != "4"){
        result = "Bad pin number";
        return SOAP_OK;
    }
        
    static int portState = 0;
    CGPIOClass gpio("4");
    gpio.export_gpio();
    gpio.setdir_gpio("out");
    if (portState){
        portState = 0;
        gpio.setval_gpio("0");
        result = "OK_0";
    }else{
        portState = 1;
        gpio.setval_gpio("1");
        result = "OK_1";
    }
    gpio.unexport_gpio();
    
    return SOAP_OK;
}

void CSoapServer::start() {
    int error = run(1234);
    cout << "start server error code: " << error << endl;
}

