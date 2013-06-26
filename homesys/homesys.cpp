#include "homesys.h"
#include "../can_devices/CCanSimpleSwitchActor.h"

CApplication::CApplication() {
    configuration = CConfiguration::getInstance();
    devicesConfig = CDevicesConfig::getInstance();
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

   
    CCan232 *can232device = new CCan232();
    can232device->initCan232Device();


    CCanSimpleSwitchActor actorSwitch;
    actorSwitch.setCommunicationProtocol(can232device);
        
    
    //    buffer.insertId(4);
    //    buffer << (unsigned char) 1;
    //    buffer << (unsigned char) 2;
    //    buffer << (unsigned char) 3;
    //    can232device.sendCanFrame(buffer);

    string x = "";
    while (1) {
        cout << "\r\n?? ";
        cin >> x;
        if (x == "reset") {
            cout<<"> reset addresses"<<endl;
            actorSwitch.resetAddresses();
        }
        
        if (x == "poll") {
            cout<<"> poll GUIDs"<<endl;
            actorSwitch.pollGUID();
        }
        
        if (x == "read") {
            cout<<"> read GUIDs"<<endl;
            actorSwitch.getGUIDs();
        }
        
        if (x == "assign") {
            cout<<"> assign addresses"<<endl;
            actorSwitch.assignAddress();
        }
        
        if (x == "list") {
            cout<<"> list addresses"<<endl;
            actorSwitch.listAddresses();
        }

        if (x == "ping") {
            cout<<"> adr? ";
            unsigned char a;
            cin >> a;
            if (actorSwitch.ping(a - 0x30))
                cout<<"ping OK"<<endl;
            else
                cout<<"ping FAILED"<<endl;
        }
        
        if (x == "check") {
            cout<<"> check devices availability"<<endl;
            actorSwitch.checkDevicesAvailability();
        }
        
        if (x == "name") {
            unsigned char adr, cat;
            cout<<"address?";
            cin >> adr;
            cout<<"enter name? ";
            string a;
            cin >> a;
            cout<<"category? ";
            cin>>cat;
            actorSwitch.setDeviceName(adr - 0x30, a, (EDeviceCategory)(cat - 0x30));
        }
       
        x = "";
        //sleep(1);
    }
}

void CApplication::dbConfig() {
    map<string, string> can232config;
    can232config["portName"] = "/dev/ttyAMA0";
    can232config["CANspeed"] = "160000";
    configuration->updateList<string>("can232", can232config);
    
    map<string, unsigned int>canConfig;
    canConfig["acceptMask0"] = 0x3ff;
    canConfig["acceptMask1"] = 0x3ff;
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
