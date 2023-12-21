////////////////////////////////////////////////////////////////////////////////
// Filename: timerclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TIMERCLASS_H_
#define _TIMERCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <sys/time.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TimerClass
////////////////////////////////////////////////////////////////////////////////
class TimerClass
{
public:
    TimerClass();
    TimerClass(const TimerClass&);
    ~TimerClass();

    void Initialize();
    void Frame();

    int GetTime();

private:
    long m_startSeconds, m_startMilliseconds;
    int m_frameTime;
};

#endif