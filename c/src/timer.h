#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

struct Timer{
  long startSeconds, startMilliseconds;
  int frameTime;
};
void InitializeTimer(Timer &timer);

void TimerFrame(Timer & timer);

#endif
