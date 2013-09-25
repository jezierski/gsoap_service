/* 
 * File:   CSoapServer.cpp
 * Author: Jezierski
 * 
 * Created on 18 marzec 2013, 21:18
 */

#include "CSoapServer.h"

CSoapServer::CSoapServer() {
    log = CLog::getInstance();
    converter = CParamsConverter::getInstance();
}

//CSoapServer::CSoapServer(const CSoapServer& orig) {
//}

CSoapServer::~CSoapServer() {
}

void CSoapServer::assignActionManager(CActionManager* actionManager) {
    this->actionManager = actionManager;
}

int CSoapServer::getCurrentTime(string& currentTime) {
    time_t rawtime;
    time(&rawtime);
    string strTime(ctime(&rawtime));
    currentTime = strTime;
    return SOAP_OK;
}

int CSoapServer::getValue(string id, string &result) {
    result = "Text etnered: " + id;
    return SOAP_OK;
}
//zrobic tablice funkcji ktore zamieniaja w zaleznosci od komendy (lub nawet kategorii) odpowiednie parametry na BLOB -> mapy lub mapy map z funkcjami konwertujacymi zmienne

int CSoapServer::switchPort(string pinNo, string &result) {
    static int portState = 0;
    CGPIOClass gpio(pinNo);
    gpio.export_gpio();
    gpio.setdir_gpio("out");
    if (portState) {
        portState = 0;
        gpio.setval_gpio("0");
        result = "OK_0";
        std::cout << "port " << pinNo << " OFF" << std::endl;
    } else {
        portState = 1;
        gpio.setval_gpio("1");
        result = "OK_1";
        std::cout << "port " << pinNo << " ON" << std::endl;
    }
    gpio.unexport_gpio();

    return SOAP_OK;
}

int CSoapServer::makeRemoteAction(LONG64 guid, LONG64 luid, LONG64 category, LONG64 command, LONG64 params, LONG64 &result) {
    result = 0;
    SAction action;
    action.command = command;
    action.params = converter->use(category, command, params);
    action.device.category = static_cast<EDeviceCategory>(category);
    action.device.guid = guid;
    action.device.luid = luid;
    actionManager->addAction(action);
    cout << "makeRemoteAction, guid: " << guid << ", luid: " << luid << ", cat: " << category << ", comm: " << command << endl;
    return 0;
}

void CSoapServer::start() {
    int error;
    while (1) {
        error = run(1234);
        if (error != SOAP_OK)
            log->error("SOAP server error code: " + to_string(error));
    }
}

