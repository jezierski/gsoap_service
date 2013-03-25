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

void CSoapServer::start() {
    int error = run(1234);
    cout << "start server error code: " << error << endl;
}