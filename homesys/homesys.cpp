#include "homesys.h"

CApplication::CApplication() {
    configuration = CConfiguration::getInstance();
    devicesConfig = CDevicesConfig::getInstance();
    log = CLog::getInstance();
}

CApplication::~CApplication() {

}

void CApplication::run() {

    log->info("Server starting...");
    //    cout<<"starting GSOAP..."<<endl;
    CSoapServer server;
    //    server.start();




    CCan232 *can232device = new CCan232();
    can232device->initCan232Device();


    CCanSimpleSwitchActor actorSwitch;
    actorSwitch.setCommunicationProtocol(can232device);

    CCanSimpleSwitchSensor sensorSwitch;
    sensorSwitch.setCommunicationProtocol(can232device);

    CDeviceManager * deviceManager = new CDeviceManager();
    deviceManager->addCategoryDevice(&actorSwitch);
    deviceManager->addCategoryDevice(&sensorSwitch);


    COperation op;
    op.loadOperations();

    deviceManager->initialize();

    SDeviceDescription global;
    global.category = EDeviceCategory::ALL;
    string x = "";
    Blob null;
    while (1) {
        cout << "\r\n?? ";
        cin >> x;
        if (x == "db") {
            try { //@TODO objac trykaczem funkcje inicjalizacyjne
                dbConfig();

            } catch (string e) {
                cout << " dbConfig: " << e << endl;
            }
        }
        if (x == "reset") {
            SDeviceDescription s;
            cout << "cat (0-all, 1-a, 2-b)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                default:
                    s = global;
            }
            deviceManager->invokeRemoteAction(s, ACTION_RESET_CATEGORY, null);
        }

        if (x == "list") {
            SDeviceDescription s;
            cout << "cat (0-all, 1-a, 2-b)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                default:
                    s = global;
            }
            deviceManager->invokeRemoteAction(s, ACTION_LIST, null);
        }

        if (x == "search") {
            cout << "cat (0-all, 1-a, 2-b)? ";
            int c;
            SDeviceDescription s;
            cin >> c;
            switch (c) {
                case 0:
                    s = global;
                    break;
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
            }
            deviceManager->invokeRemoteAction(s, ACTION_SEARCH_DEVICES, null);
        }



        if (x == "ping") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            cout << "cat (1-a, 2-b)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
            }
            s.guid = g;
            s.luid = (unsigned char) l;
            deviceManager->invokeRemoteAction(s, ACTION_PING, null);
        }

        if (x == "check") {
            cout << "cat (0-all, 1-a, 2-b)? ";
            int c;
            SDeviceDescription s;
            cin >> c;
            switch (c) {
                case 0:
                    s = global;
                    break;
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
            }
            deviceManager->invokeRemoteAction(s, ACTION_CHECK_AVAILABILITY, null);
        }

        if (x == "name") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            cout << "cat (1-a, 2-b)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
            }
            cout << "name ? ";
            string n;
            cin >> n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_DEVICE_NAME].put<string>(n);
            deviceManager->invokeRemoteAction(s, ACTION_SET_NAME, b);
        }

        if (x == "set") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_SIMPLE_SWITCH;

            cout << "value ? ";
            int n;
            cin >> n;
            Params par;
            par.push_back((unsigned char) n);
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_ACTION_PARAMETER].put<Params>(par);
            deviceManager->invokeRemoteAction(s, ACTION_SET_OUTPUT, b);

        }

        x = "";
        //sleep(1);
    }
}

void CApplication::dbConfig() {
    log->info("Loading database...");
    map<string, string> can232config;
    can232config["portName"] = "/dev/ttyAMA0";
    can232config["CANspeed"] = "160000";
    configuration->updateList<string>("can232", can232config);

    map<string, unsigned int>canConfig;
    canConfig["acceptMask0"] = 0x3ff;
    canConfig["acceptMask1"] = 0x3ff;
    canConfig["acceptFilter0"] = 200;
    canConfig["acceptFilter1"] = 200;
    canConfig["acceptFilter2"] = 200;
    canConfig["acceptFilter3"] = 200;
    canConfig["acceptFilter4"] = 200;
    canConfig["acceptFilter5"] = 200;

    configuration->updateList<unsigned int>("canConfig", canConfig);


    log->success("Loading database success");
}

int main() {

    CApplication *application = new CApplication();

    application->run();

    return 0;
}
