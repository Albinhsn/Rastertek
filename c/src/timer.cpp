#include "timer.h"

void InitializeTimer(Timer &timer){

  struct timeval time;
  gettimeofday(&time, 0);

  timer.startSeconds = time.tv_sec;
  timer.startMilliseconds = time.tv_usec / 1000;

}

void TimerFrame(Timer & timer){
  struct timeval time;
  long seconds, microseconds, secondsDelta, milliseconds, currentMs;
  
  gettimeofday(&time, 0);
  seconds = time.tv_sec;
  microseconds = time.tv_usec;

  milliseconds = microseconds / 1000;
  secondsDelta = seconds - timer.startSeconds;
  currentMs = (secondsDelta * 1000) + milliseconds;
  timer.frameTime = (int)(currentMs - timer.startMilliseconds);

  gettimeofday(&time, 0);
  timer.startSeconds = time.tv_sec;
  timer.startMilliseconds = time.tv_usec / 1000;

}
