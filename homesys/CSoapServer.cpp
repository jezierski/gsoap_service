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

int CSoapServer::getCurrentTime(string& time){
    time = "12:34";
    
   return SOAP_OK; 
}
