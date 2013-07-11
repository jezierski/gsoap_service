
#ifndef CTOOLS_H
#define	CTOOLS_H
#define SHOW(x) cout << #x << " = [ " << x << " ] " << endl;
#define show SHOW
#include <unistd.h>
#include <sstream>
#include <climits>
#include <string>
#include <algorithm>
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
inline T fromString(const std::string& s) {
    std::istringstream stream(s);
    T t;
    stream >> t;
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

inline bool operator == (SDeviceDescription dev1, SDeviceDescription dev2){
    return (dev1.guid == dev2.guid && dev1.luid == dev2.luid);
}

inline string to_string(SDeviceDescription device){
    string output = "[GUID: " + to_string((unsigned int)device.guid) + " LUID: " + to_string((unsigned int)device.luid) + ", ADR: " + to_string((unsigned int)device.address) + " CAT: " + to_string((unsigned int)device.category) + " NAME: " + device.name + "]";
    return output;
}

class CTools {
public:
    CTools();
    CTools(const CTools& orig);
    virtual ~CTools();
private:

};

#endif	/* CTOOLS_H */

