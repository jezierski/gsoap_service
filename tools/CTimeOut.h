

#ifndef _CTIMEOUT_H
#define	_CTIMEOUT_H

#include <ctime>
#include <sys/time.h>

class CTimeOut
{
public:
    CTimeOut();
    virtual ~CTimeOut();

    void StartTimeOut(int Tout);
    bool IsTimeOut();
    void GetTimer(void);
    void SetMilliSec(int Tout) { StartTimeOut(Tout);};
    bool Elapse(void) {return IsTimeOut();};

private:
    clock_t m_TimeOut;
    clock_t m_TimerTicks;
    clock_t m_msTimer;
    clock_t m_msDiv;
    struct timeval time;
  
};

#endif	/* _CTIMEOUT_H */

