#include <stdlib.h>

#include "homesys.h"

CApplication::CApplication(vector<string> params) {
    configuration = CConfiguration::getInstance();
    devicesConfig = CDevicesConfig::getInstance();
    log = CLog::getInstance();
    appParams = params;
}

CApplication::~CApplication() {

}

void CApplication::assignSlots() {
    for (CDevice *device : deviceManager->getDevices()) {
        device->sensorEvent.Connect(actionTranslator, &CActionTranslator::updateDeviceState);
    }
    timer->timerEvent.Connect(actionTranslator, &CActionTranslator::updateTimerStack);
    soapServer->operationLoad.Connect(actionTranslator, &CActionTranslator::loadOperations);
}

bool CApplication::modeWithInit() {
    for (auto param : appParams) {
        if (param == "noInit")
            return false;
    }
    return true;
}

void CApplication::run() {

    log->info("Server starting...");



    CCanSimpleSwitchActor *actorSwitch = new CCanSimpleSwitchActor();
    CCanSimpleSwitchSensor *sensorSwitch = new CCanSimpleSwitchSensor();
    CCanRGBActor *rgbDriver = new CCanRGBActor();
    CCanPWMActor *pwmDriver = new CCanPWMActor();
    CDevice *bootDevice = new CDevice();




    try {
        soapServer = new CSoapServer();
        can232device = new CCan232();
        can232device->initCan232Device();
        bootDevice->setCommunicationProtocol(can232device);
        actorSwitch->setCommunicationProtocol(can232device);
        sensorSwitch->setCommunicationProtocol(can232device);
        rgbDriver->setCommunicationProtocol(can232device);
        pwmDriver->setCommunicationProtocol(can232device);

        deviceManager = new CDeviceManager();
        deviceManager->addBootDevice(bootDevice);
        deviceManager->addCategoryDevice(actorSwitch);
        deviceManager->addCategoryDevice(sensorSwitch);
        deviceManager->addCategoryDevice(rgbDriver);
        deviceManager->addCategoryDevice(pwmDriver);


        timer = new CTimer();

        actionTranslator = new CActionTranslator();
        actionTranslator->assignDeviceManager(deviceManager);
        actionTranslator->assignTimer(timer);
        actionTranslator->loadOperations();


        if (modeWithInit()) {
            deviceManager->initialize();
        }

        soapServer->assignDeviceManager(deviceManager);
        new thread(&CSoapServer::start, soapServer);
    } catch (string err) {
        log->error("Starting system failed: " + err);
        exit(0);
    }

    new thread(&CDeviceManager::runInThreadGlobalRemoteAction, deviceManager, ACTION_READ_NEW_STATUS, Blob());
    new thread(&CActionTranslator::translateActions, actionTranslator);
    new thread(&CTimer::run, timer);
    assignSlots();


    string x = "";
    SDeviceDescription global;
    global.category = EDeviceCategory::ALL;
    Blob null;
    while (1) {
        cout << "\r\n?? ";
        cin >> x;
        if (x == "help") {
            cout << "boot\t - enter a device into boot mode" << endl;
            cout << "upload\t - upload firmware" << endl;
            cout << "files\t - show firmware files list" << endl;
            cout << "db\t - write default settings to DataBase" << endl;
            cout << "reset\t - reset devices addresses" << endl;
            cout << "search\t - search devices without address" << endl;
            cout << "resstat\t - reset sensors statuses" << endl;
            cout << "newstat\t - check sensors new statuses" << endl;
            cout << "trans\t - load operations" << endl;
            cout << "chain\t - load chain actions" << endl;
            cout << "list\t - print devices list" << endl;
            cout << "ping\t - ping device" << endl;
            cout << "check\t - check device availability" << endl;
            cout << "name\t - set device name" << endl;
            cout << "set\t - set actor status" << endl;
            cout << "get\t - get actor status" << endl;
            cout << "sensor\t - read sensor status" << endl;
            cout << "rgbmode\t - set RGB mode" << endl;
            cout << "rgbspeed\t - set RGB speed" << endl;
            cout << "rgbr\t - set RGB red" << endl;
            cout << "rgbg\t - set RGB green" << endl;
            cout << "rgbb\t - set RGB blue" << endl;
            cout << "rgball\t - set RGB all" << endl;
            cout << "rgbgetspeed\t - get RGB speed" << endl;
            cout << "pwm\t - set PWM" << endl;
            cout << "pwmget\t - get PWM" << endl;
            cout << "pwmall\t - set all PWM" << endl;
            cout << "pwmsame\t - set all the same PWM" << endl;
            cout << "pwmup\t - increase PWM" << endl;
            cout << "pwmdown\t - decrease PWM" << endl;
            cout << "pwmupall\t - increase all PWM" << endl;
            cout << "pwmdownall\t - decrease all PWM" << endl;
        }
        if (x == "db") {
            try { //@TODO objac trykaczem funkcje inicjalizacyjne
                dbConfig();

            } catch (string e) {
                cout << " dbConfig: " << e << endl;
            }
        }
        if (x == "boot") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "cat (1-actor, 2-sensor, 3-rgb, 4-pwm)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
                    break;
            }
            s.guid = g;
            s.luid = (unsigned char) 0;
            deviceManager->invokeRemoteAction(s, ACTION_BOOT, null);
        }
        if (x == "upload") {
            string fname;
            cout << "enter filename: " << flush;
            cin >> fname;
            deviceManager->uploadFirmware(fname);
        }

        if (x == "files") {
            vector<string> list = deviceManager->getFirmwareFilesList();
            for (string f : list) {
                cout << f << endl;
            }
        }

        if (x == "reset") {
            SDeviceDescription s;
            cout << "cat (0-all, 1-actor, 2-sensor, 3-rgb, 4-pwm)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
                    break;
                default:
                    s = global;
            }
            deviceManager->invokeRemoteAction(s, ACTION_RESET_CATEGORY, null);
        }

        if (x == "resstat") {
            deviceManager->invokeRemoteAction(global, ACTION_RESET_ALL_STATUS, null);
        }

        if (x == "newstat") {
            deviceManager->invokeRemoteAction(global, ACTION_READ_NEW_STATUS, null);
        }

        if (x == "trans") {
            try {
                actionTranslator->loadOperations();
            } catch (string e) {
                cout << e << endl;
            }
        }

        if (x == "chain") {
            try {
                deviceManager->loadActionsChain();
            } catch (string e) {
                cout << e << endl;
            }
        }

        if (x == "list") {
            SDeviceDescription s;
            cout << "cat (0-all, 1-actor, 2-sensor, 3-RGB, 4-PWM)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
                    break;
                default:
                    s = global;
            }
            deviceManager->invokeRemoteAction(s, ACTION_LIST, null);
        }

        if (x == "search") {
            cout << "cat (0-all, 1-actor, 2-sensor, 3-rgb, 4-pwm)? ";
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
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
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
            cout << "cat (1-actor, 2-sensor, 3-rgb, 4-pwm)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                    break;
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
                    break;
            }
            s.guid = g;
            s.luid = (unsigned char) l;
            deviceManager->invokeRemoteAction(s, ACTION_PING, null);
        }

        if (x == "check") {
            cout << "cat (0-all, 1-actor, 2-sensor)? ";
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
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
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
            cout << "cat (1-actor, 2-sensor, 3-RGB, 4-PWM)? ";
            int c;
            cin >> c;
            switch (c) {
                case 1:
                    s.category = EDeviceCategory::A_SIMPLE_SWITCH;
                    break;
                case 2:
                    s.category = EDeviceCategory::S_SIMPLE_SWITCH;
                case 3:
                    s.category = EDeviceCategory::A_RGB_DRIVER;
                    break;
                case 4:
                    s.category = EDeviceCategory::A_PWM_DRIVER;
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

        if (x == "pwmget") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b = deviceManager->invokeRemoteAction(s, ACTION_GET_PWM, null);
            cout << "response: " << b[BLOB_TXT_RESPONSE_RESULT].get<string>() << endl;
        }

        if (x == "pwmdownall") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_CHANGE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_PWM_DOWN_ALL, b);

        }

        if (x == "pwmupall") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_CHANGE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_PWM_UP_ALL, b);

        }

        if (x == "pwmdown") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_CHANGE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_PWM_DOWN, b);

        }

        if (x == "pwmup") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_CHANGE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_PWM_UP, b);

        }

        if (x == "pwmsame") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_VALUE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_SET_PWM_ALL_THE_SAME, b);

        }


        if (x == "pwmall") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            unsigned int l;
            cout << "start luid ? ";
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            int n;
            Params p;
            cout << "value of 0? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 1? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 2? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 3? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 4? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_ACTION_PARAMETER].put<Params>(p);
            deviceManager->invokeRemoteAction(s, ACTION_SET_PWM_ALL, b);
            p.clear();

            cout << "start luid ? ";
            cin >> l;
            cout << "value of 5? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 6? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 7? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 8? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 9? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            s.luid = (unsigned char) l;
            Blob b2;
            b2[BLOB_ACTION_PARAMETER].put<Params>(p);
            deviceManager->invokeRemoteAction(s, ACTION_SET_PWM_ALL, b2);
            p.clear();

            cout << "start luid ? ";
            cin >> l;
            cout << "value of 10? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 11? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 12? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            cout << "value of 13? (0-255)";
            cin >> n;
            p.push_back((unsigned char) n);
            s.luid = (unsigned char) l;
            Blob b3;
            b3[BLOB_ACTION_PARAMETER].put<Params>(p);
            deviceManager->invokeRemoteAction(s, ACTION_SET_PWM_ALL, b3);

        }

        if (x == "pwm") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_PWM_DRIVER;

            cout << "value ? (0-255)";
            int n;
            cin >> n;
            unsigned char p;
            p = (unsigned char) n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_PWM_VALUE].put<unsigned char>(p);
            deviceManager->invokeRemoteAction(s, ACTION_SET_PWM, b);

        }

        if (x == "rgbg") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            cout << "value ? (0-0xfff)";
            unsigned int n;
            cin >> n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_RGB_CHANNEL].put<unsigned int>(n);
            deviceManager->invokeRemoteAction(s, ACTION_SET_CHANNEL_GREEN, b);

        }

        if (x == "rgbb") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            cout << "value ? (0-0xfff)";
            unsigned int n;
            cin >> n;
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_RGB_CHANNEL].put<unsigned int>(n);
            deviceManager->invokeRemoteAction(s, ACTION_SET_CHANNEL_BLUE, b);

        }

        if (x == "rgball") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            cout << "R value ? (0-0xfff)";
            vector<unsigned int> values;
            unsigned int n;
            cin >> n;
            values.push_back(n);
            cout << "G value ? (0-0xfff)";
            cin >> n;
            values.push_back(n);
            cout << "B value ? (0-0xfff)";
            cin >> n;
            values.push_back(n);
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_RGB_ALL].put < vector<unsigned int >> (values);
            deviceManager->invokeRemoteAction(s, ACTION_SET_CHANNEL_ALL, b);

        }

        if (x == "rgbmode") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            cout << "value ? (0-OFF, 1-ALL_AUTO, 2-CHAIN_AUTO, 3-RND, 4-SIMPLE)";
            int n;
            cin >> n;
            Params par;
            par.push_back((unsigned char) n);
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_ACTION_PARAMETER].put<Params>(par);
            deviceManager->invokeRemoteAction(s, ACTION_SET_MODE, b);

        }

        if (x == "rgbspeed") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            cout << "value ? (0-2)";
            int n;
            cin >> n;
            Params par;
            par.push_back((unsigned char) n);
            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b[BLOB_ACTION_PARAMETER].put<Params>(par);
            deviceManager->invokeRemoteAction(s, ACTION_SET_SPEED, b);

        }

        if (x == "rgbgetspeed") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_RGB_DRIVER;

            s.guid = g;
            s.luid = (unsigned char) l;
            Blob b;
            b = deviceManager->invokeRemoteAction(s, ACTION_GET_SPEED, null);
            cout << "response: " << b[BLOB_TXT_RESPONSE_RESULT].get<string>() << endl;
        }

        if (x == "sensor") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::S_SIMPLE_SWITCH;

            s.guid = g;
            s.luid = (unsigned char) l;
            deviceManager->invokeRemoteAction(s, ACTION_READ_SENSOR_STATUS, null);

        }

        if (x == "get") {
            SDeviceDescription s;
            cout << "guid ? ";
            unsigned int g;
            cin >> g;
            cout << "luid ? ";
            unsigned int l;
            cin >> l;
            s.category = EDeviceCategory::A_SIMPLE_SWITCH;

            s.guid = g;
            s.luid = (unsigned char) l;
            deviceManager->invokeRemoteAction(s, ACTION_GET_OUTPUT, null);

        }

        x = "";
        msleep(100);
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

int getProcIdByName(string procName)
{
    int pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                string cmdPath = string("/proc/") + dirp->d_name + "/cmdline";
                ifstream cmdFile(cmdPath.c_str());
                string cmdLine;
                getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Compare against requested process name
                    if (procName == cmdLine)
                        pid = id;
                }
            }
        }
    }

    closedir(dp);

    return pid;
}

void checkAppInstance() {
    int runningPID = getProcIdByName("homik");
        
    pid_t pid = getpid();
    string spid;
    fstream file;
    file.open("homik.pid", ios_base::out | ios_base::in);
    if (file.is_open()) {
        getline(file, spid);
        file.close();
     
        if (spid == to_string(runningPID)) {
            cout << "Process already running, quit..." << endl;
            exit(1);
        } else {
            unlink("homik.pid");
            file.clear();
            file.open("homik.pid", ios_base::out);
            file << pid;
            file.close();
        }
    } else {
        file.clear();
        file.open("homik.pid", ios_base::out);
        file << pid;
        file.close();
    }
}


void exitFunction() {
    pid_t pid = getpid();
    string spid;
    fstream file;
    file.open("homik.pid", ios_base::in);
    if (file.is_open()) {
        getline(file, spid);
        file.close();
    }
    if (spid == to_string(pid)) {
        unlink("homik.pid");
    }

}


int main(int argc, char *argv[]) {

    vector<string> params;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        params.push_back(arg);
    }

    atexit(exitFunction);
    checkAppInstance();

    CApplication *application = new CApplication(params);

    application->run();

    return 0;
}
