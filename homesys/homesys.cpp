#include "homesys.h"

CApplication::CApplication() {
    configuration = CConfiguration::getInstance();
    db = CDatabase::getInstance();
}

CApplication::~CApplication() {

}

void CApplication::run() {
    cout << "application is running...." << endl;
    //    cout<<"starting GSOAP..."<<endl;
    CSoapServer server;
    //    server.start();
    
    try { //@TODO objac trykaczem funkcje inicjalizacyjne
        dbConfig();
    } catch (string e) {
        cout << " dbConfig: " << e << endl;
    }

    CCan232 can232device;
    can232device.initCan232Device();


    CCanBuffer buffer;
    unsigned char data1, data2, dataId;
    //    buffer.insertId(4);
    //    buffer << (unsigned char) 1;
    //    buffer << (unsigned char) 2;
    //    buffer << (unsigned char) 3;
    //    can232device.sendCanFrame(buffer);

    char x;
    while (1) {
        //cout << "next ?";
        //cin >> x;
        //if (x == 'n') {

        buffer = can232device.getCanFrame();
        if (buffer.frameId()) {
            cout << "id: " << (int) buffer.frameId() << endl;
            data1 = buffer[0];
            data2 = buffer[1];
            dataId = buffer[2];
            buffer.printBuffer();
        }
        if (dataId == 3) {
            buffer.clear();
            buffer.insertId(4);
            buffer << (unsigned char) 0x34;
            buffer << (unsigned char) 0x34;
            buffer << (unsigned char) 0x34;
            buffer << (unsigned char) data1;
            buffer << (unsigned char) data2;
            can232device.sendCanFrame(buffer);
            dataId = 0;
        }
        if (dataId == 4) {
            buffer.clear();
            buffer.insertId(3);
            buffer << (unsigned char) 0x33;
            buffer << (unsigned char) 0x33;
            buffer << (unsigned char) 0x33;
            buffer << (unsigned char) data1;
            buffer << (unsigned char) data2;
            can232device.sendCanFrame(buffer);
            dataId = 0;
        }
        //cout << "Received buffer empty" << endl;
        //  }
        //            x = 0;
        msleep(1);
        //sleep(1);
    }
}

void CApplication::dbConfig() {
    map<string, string> can232config;
    can232config["portName"] = "/dev/ttyAMA0";
    can232config["CANspeed"] = "160000";
    configuration->updateList<string>("can232", can232config);
    
    map<string, unsigned int>canConfig;
    canConfig["acceptMask0"] = 0x002;
    canConfig["acceptMask1"] = 0x002;
    canConfig["acceptFilter0"] = 0x002;
    canConfig["acceptFilter1"] = 0x002;
    canConfig["acceptFilter2"] = 0x002;
    canConfig["acceptFilter3"] = 0x002;
    canConfig["acceptFilter4"] = 0x002;
    canConfig["acceptFilter5"] = 0x002;
    configuration->updateList<unsigned int>("canConfig", canConfig);

}

int main() {

    CApplication *application = new CApplication();

    application->run();

    return 0;
}
