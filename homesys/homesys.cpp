#include "homesys.h"
#include "../can_devices/CCanSimpleSwitchActor.h"
#include "../can_devices/CCanSimpleSwitchSensor.h"
#include "CDeviceManager.h"

CApplication::CApplication() {
    configuration = CConfiguration::getInstance();
    devicesConfig = CDevicesConfig::getInstance();
}

CApplication::~CApplication() {

}

void CApplication::run() {
    CDeviceManager * deviceManager = new CDeviceManager();
    CCanSimpleSwitchActor actor;
    CCanSimpleSwitchSensor sensor;
    
    SDeviceDescription d1, d2, d3, d4, d5, d6;
    d1.address = 11;
    d1.category = EDeviceCategory::A_SIMPLE_SWITCH;
    d1.guid = 123;
    d1.luid = 1;
    d1.name = "jeden A";
    actor.addCategoryDevice(d1);
    d2.address = 22;
    d2.category = EDeviceCategory::A_SIMPLE_SWITCH;
    d2.guid = 123;
    d2.luid = 2;
    d2.name = "dwa A";
    actor.addCategoryDevice(d2);
    d3.address = 1;
    d3.category = EDeviceCategory::A_SIMPLE_SWITCH;
    d3.guid = 321;
    d3.luid = 1;
    d3.name = "trzy A";
    actor.addCategoryDevice(d3);
    d4.address = 44;
    d4.category = EDeviceCategory::S_SIMPLE_SWITCH;
    d4.guid = 456;
    d4.luid = 1;
    d4.name = "jeden S";
    sensor.addCategoryDevice(d4);
    d5.address = 55;
    d5.category = EDeviceCategory::S_SIMPLE_SWITCH;
    d5.guid = 456;
    d5.luid = 2;
    d5.name = "dwa S";
    sensor.addCategoryDevice(d5);
    d6.address = 66;
    d6.category = EDeviceCategory::S_SIMPLE_SWITCH;
    d6.guid = 654;
    d6.luid = 1;
    d6.name = "trzy S";
    sensor.addCategoryDevice(d6);

    deviceManager->addCategoryDevice(&actor);
    deviceManager->addCategoryDevice(&sensor);

    Params p0, p1, p2, p3;
    p1.push_back(111);
    p2.push_back(111);
    p2.push_back(222);
    p3.push_back(231);
    p3.push_back(222);
    p3.push_back(111);
    deviceManager->invokeRemoteFunction(d5, 1, p0);
    deviceManager->invokeRemoteFunction(d6, 2, p1);
    deviceManager->invokeRemoteFunction(d4, 1, p2);
    deviceManager->invokeRemoteFunction(d3, 2, p3);
    deviceManager->invokeRemoteFunction(d2, 1, p0);
    
    return;
    
    
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
