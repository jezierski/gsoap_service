

#ifndef CLOG_H
#define CLOG_H
#include <string>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include "CTools.h"
#define put_line(str, level)    put(__FILE__ + string(":") + to_string(__LINE__) + string("->") + string(str), level)
#define           NC "\033[0m"
#define  HOME_CURSOR "\E[0;0H"
#define CLEAR_SCREEN "\E[2J"

using namespace std;

class CLog {
public:
    string ver;
    int resetTimer();
    int printVersion();

    enum logType {
        INFO,
        WARNING,
        ERROR,
        SUCCESS
    };


    int put(string str, logType level = INFO);
    int error(string str);
    int warning(string str);
    int success(string str);
    int info(string str);

    void log2syslog(string msg, logType level);


    static CLog * getInstance();

private:
    struct timeval start, end;
    unsigned long mtime, seconds, useconds;
    unsigned char resetFlag;
    CLog();
    static CLog *instance;
    //CLog(const CLog &);
    // CLog& operator=(const CLog&);
    unsigned long appStartTime;
    string level2str(logType level);


};

#endif  /* CLOG_H */
