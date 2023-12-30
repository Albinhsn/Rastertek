#include "fps.h"
#include <sys/select.h>

void InitializeFPS(FPS &fps) {
    struct timeval time;

    fps.fps = 0;
    fps.count = 0;

    gettimeofday(&time, 0);

    fps.startSeconds = time.tv_sec;
    fps.startMilliseconds = time.tv_usec / 1000;
}

void UpdateFPSPerFrame(FPS &fps) {

    struct timeval time;
    long seconds, microseconds, secondsDelta, milliseconds, currentMs;

    fps.count++;
    gettimeofday(&time, 0);
    seconds = time.tv_sec;
    microseconds = time.tv_usec;

    milliseconds = microseconds / 1000;
    secondsDelta = seconds - fps.startSeconds;
    currentMs = (secondsDelta * 1000) + milliseconds;
    currentMs = currentMs - fps.startMilliseconds;

    if (currentMs >= 1000) {
        fps.fps = fps.count;
        fps.count = 0;

        gettimeofday(&time, 0);
        fps.startSeconds = time.tv_sec;
        fps.startMilliseconds = time.tv_usec / 1000;
    }
}
