#include "fpsclass.h"


FpsClass::FpsClass(){}
FpsClass::FpsClass(const FpsClass & other){}
FpsClass::~FpsClass(){}

void FpsClass::Initialize(){
  struct timeval time;

  m_fps = 0;
  m_count = 0;

  gettimeofday(&time, 0);

  m_startSeconds = time.tv_sec;
  m_startMilliseconds = time.tv_usec / 1000;
}

void FpsClass::Frame(){
  struct timeval time;
  long seconds, microseconds, secondsDelta, milliseconds, currentMs;


  m_count++;

  gettimeofday(&time, 0);
  seconds = time.tv_sec;
  microseconds = time.tv_usec;

  milliseconds = microseconds / 1000;
  secondsDelta = seconds - m_startSeconds;

  currentMs = (secondsDelta * 1000) - milliseconds;
  currentMs = currentMs - m_startMilliseconds;

  if(currentMs >= 1000){
    m_fps = m_count;
    m_count = 0;

    gettimeofday(&time, 0);
    m_startSeconds = time.tv_sec;
    m_startMilliseconds = time.tv_usec / 1000;
  }
}

int FpsClass::GetFps(){
  return m_fps;
}
