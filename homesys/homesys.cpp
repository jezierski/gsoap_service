#include "homesys.h"

CApplication::CApplication() {

}

CApplication::~CApplication() {

}

void CApplication::run() {
    cout << "application is running...." << endl;
    //    cout<<"starting GSOAP..."<<endl;
    CSoapServer server;
    //    server.start();

    CCan232 can232device;
    can232device.initCan232Device();

    CCanBuffer buffer;
    buffer.insertId(4);
    buffer << (unsigned char) 1;
    buffer << (unsigned char) 2;
    buffer << (unsigned char) 3;
    can232device.sendCanFrame(buffer);

    char x;
    while (1) {
        //cout << "next ?";
        //cin >> x;
        //if (x == 'n') {
            
            buffer = can232device.getCanFrame();
            if (buffer.frameId()) {
                cout << "id: " << (int) buffer.frameId() << endl;
                buffer.printBuffer();
            } else
                cout << "Received buffer empty" << endl;
      //  }
        x = 0;
        sleep(1);
    }
}

int main() {

    CApplication *application = new CApplication();

    application->run();

    return 0;
}
