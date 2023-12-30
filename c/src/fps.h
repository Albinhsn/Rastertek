#ifndef FPS_H
#define FPS_H

#include <sys/time.h>

struct FPS {
    int fps, count;
    long startSeconds, startMilliseconds;
};
void InitializeFPS(FPS &fps);
void UpdateFPSPerFrame(FPS &fps);

#endif
