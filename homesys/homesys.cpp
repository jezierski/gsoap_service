#include "homesys.h"
#include <iostream>

CApplication::CApplication() {

}

CApplication::~CApplication() {

}

void CApplication::run() {
    cout<<"application is running......"<<endl;

}

int main() {

    CApplication *application = new CApplication();

    application->run();

    return 0;
}
