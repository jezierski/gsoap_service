
#include "CLog.h"



CLog::CLog() {
    gettimeofday(&end, NULL);
    seconds = end.tv_sec;
    useconds = end.tv_usec;
    appStartTime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
}




int CLog::put(string str, logType level) {
  
    gettimeofday(&end, NULL);
    switch (level) {



        case CLog::ERROR:
            cout << "\033[" << 31 << "m";
            ;
            break;
        case CLog::INFO:
            cout << "\033[" << 36 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 37 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::WARNING:
            cout << "\033[" << 33 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 33 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::SUCCESS:
            cout << "\033[" << 32 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 34 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::DEBUG_ERROR:
           cout << "\033[1;" << 31 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 31 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::DEBUG_INFO:
            cout << "\033[1;" << 32 << "m";
            break;
        case CLog::DEBUG_WARNING:
            cout << "\033[1;" << 33 << "m";
            
            //cout << "\E[" << 0 << "m" << "\E[" << 32 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::LOW_DEBUG_WARNING:
            cout << "\033[1;" << 34 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 32 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::LOW_LEVEL_DEBUG:
            cout << "\033[1;" << 34 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 32 << "m" << "\E[" << 40 << "m";
            break;
        case CLog::ACTION_INFO:
            cout << "\033[1;" << 34 << "m";
            //cout << "\E[" << 0 << "m" << "\E[" << 32 << "m" << "\E[" << 40 << "m";
            break;
    };

    if (resetFlag) {
        seconds = end.tv_sec - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
        resetFlag = 0;

        cout << "Last instr. time: \t" << mtime << "ms \t";
    } else {

        seconds = end.tv_sec;
        useconds = end.tv_usec;
        mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
        cout << mtime - appStartTime << "ms \t";
    }

    cout << str << NC << endl;

    //    cout << NC;

    return 0;
}

int CLog::resetTimer() {
    resetFlag = 1;
    gettimeofday(&start, NULL);
    return 0;
}

CLog* CLog::getInstance() {
    if (!instance)
        instance = new CLog();
    return instance;

}

int CLog::warning(string message) {
    put(message, CLog::WARNING);
    return 0;
}

int CLog::error(string message) {
    put(message, CLog::ERROR);
    return 0;
}

int CLog::info(string message) {
    put(message, CLog::INFO);
    return 0;
}

int CLog::success(string message) {
    put(message, CLog::SUCCESS);
    return 0;
}



CLog *CLog::instance = NULL;

int CLog::printVersion() {
    cout << "Log version: " << ver << endl;
    return 0;
}
