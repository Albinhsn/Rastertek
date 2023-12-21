#ifndef FPSCLASS_H
#define FPSCLASS_H


#include <sys/time.h>

class FpsClass{
public: 
  FpsClass();
  FpsClass(const FpsClass&);
  ~FpsClass();
  void Initialize();
  void Frame();
  int GetFps();

private:
  int m_fps, m_count;
  long m_startSeconds;
  long m_startMilliseconds;
};

#endif
