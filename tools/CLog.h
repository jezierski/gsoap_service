

#ifndef CLOG_H
#define CLOG_H
#include <string>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#define put_line(str, level)    put(__FILE__ + string(":") + to_string(__LINE__) + string("->") + string(str), level)
#define           NC "\033[0m"
#define  HOME_CURSOR "\E[0;0H"
#define CLEAR_SCREEN "\E[2J"

using namespace std;

class CLog {
private:
    struct timeval start, end;
    unsigned long mtime, seconds, useconds;
     unsigned char resetFlag;
    CLog();
    static CLog *instance;
    //CLog(const CLog &);
    // CLog& operator=(const CLog&);
    unsigned long appStartTime;
public:
    string ver;
    int resetTimer();
    int printVersion();

        enum logType {
            INFO,
            WARNING,
            ERROR,
            SUCCESS,
            DEBUG_INFO,
            DEBUG_WARNING,
            DEBUG_ERROR,
            LOW_DEBUG_WARNING,
            LOW_LEVEL_DEBUG,
            ACTION_INFO,
        };


        int put(string str, logType level = INFO);
        int error(string str);
        int success(string str);
        int info(string str);
 
   
        static CLog * getInstance();


    };

#endif  /* CLOG_H */
