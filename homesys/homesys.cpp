#include "homesys.h"


CApplication::CApplication() {

}

CApplication::~CApplication() {

}

void CApplication::run() {
    cout<<"application is running......"<<endl;
    CSoapServer server;
    server.start();
    
    while(1);
}

int main() {

    CApplication *application = new CApplication();

    application->run();

    return 0;
}
