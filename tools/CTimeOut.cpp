

#include "CTimeOut.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

CTimeOut::CTimeOut()
{
 }

CTimeOut::~CTimeOut()
{

}


void CTimeOut::StartTimeOut(int Tout)
{
        GetTimer();
	m_TimeOut= m_msTimer + Tout;
  	return ;
}


bool CTimeOut::IsTimeOut(void)
{
    bool elapse;

    GetTimer();

   // elapse= ((m_msTimer ^ m_TimeOut) & 0x8000) ? (m_msTimer & 0x7fff) < (m_TimeOut & 0x7fff)
//                                               : (m_msTimer & 0x7fff) > (m_TimeOut & 0x7fff);
                                               
    elapse = (m_msTimer >= m_TimeOut );
   
                                               
    return elapse;
}

void CTimeOut::GetTimer(void)
{
    gettimeofday(&time, NULL);
    m_msTimer= ((time.tv_sec) * 1000 + time.tv_usec / 1000.0) + 0.5;
}
