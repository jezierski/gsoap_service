
#ifndef CTOOLS_H
#define	CTOOLS_H
#define SHOW(x) cout << #x << " = [ " << x << " ] " << endl;
#define show SHOW
#include <unistd.h>
#include <sstream>
#include <climits>
#include <string>
#include <algorithm>
#include <time.h>
#include "types.h"

template <class T>
inline std::string to_string(const T& t, bool hex = false) {
    std::stringstream ss;
    if (hex)
        ss << std::hex << t << std::dec;
    else
        ss << t;
    //ss.uppercase;
    return ss.str();
}

template<class T>
inline T fromString(const std::string& s, bool hex = false) {
    T t;
    if (hex) {
        std::stringstream ss;
        ss << std::hex << s;
        ss >> t;
    } else {
        std::istringstream stream(s);
        stream >> t;
    }
    return t;
}

inline bool is_number(const std::string& s) {
    return !s.empty() && find_if(s.begin(),
            s.end(), [](char c) {
                return !std::isdigit(c); }) == s.end();
}

inline void msleep(const unsigned int ms) {
    usleep(ms * 1000);
}

inline bool operator ==(SDeviceDescription dev1, SDeviceDescription dev2) {
    return (dev1.guid == dev2.guid && dev1.luid == dev2.luid);
}

inline string to_string(EDeviceCategory category) {
    switch (category) {
        case EDeviceCategory::ALL:
            return "ALL";
        case EDeviceCategory::A_SIMPLE_SWITCH:
            return "A_SIMPLE_SWITCH";
        case EDeviceCategory::S_SIMPLE_SWITCH:
            return "S_SIMPLE_SWITCH";
        case EDeviceCategory::A_RGB_DRIVER:
            return "A_RGB_DRIVER";
        case EDeviceCategory::MASTER:
            return "MASTER";
        case EDeviceCategory::OTHER:
            return "OTHER";
        default:
            return "UNKNOWN";
    }
}

inline string to_string(SDeviceDescription device) {
    string output = "[GUID: " + to_string((unsigned int) device.guid) + "\tLUID: " + to_string((unsigned int) device.luid) + "\t\tCAT: " + to_string(device.category) + "\tNAME: " + device.name + "]";
    return output;
}

inline string to_string(Params params) {
    string output = "";
    for (unsigned char param : params){
        output += to_string((int)param, true) + " ";
    }
    if (output.length() > 1){
        output = output.substr(0, output.length() - 1);
    }
    return output;
}

inline long long getCurrentDayTime() {
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    long long secs = timeinfo->tm_hour * 3600 + timeinfo->tm_min * 60 + timeinfo->tm_sec;
    return secs;
}


class CTools {
public:
    CTools();
    CTools(const CTools& orig);
    virtual ~CTools();
private:

};

#endif	/* CTOOLS_H */

