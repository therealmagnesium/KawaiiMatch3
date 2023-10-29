#include "Timer.h"
#include <raylib.h>
#include <stdlib.h>

void ResetTimer(Timer* timer, float lifetime)
{
    if (timer != NULL)
    {
        timer->lifetime = lifetime;
        timer->hasStarted = false;
    }
}

void StartTimer(Timer* timer, float lifetime)
{
    if (timer != NULL)
        timer->lifetime = lifetime;

    timer->hasStarted = true;
}

void UpdateTimer(Timer* timer)
{
    if (timer != NULL && timer->hasStarted)
    {
        if (timer != NULL && timer->lifetime > 0.f)
            timer->lifetime -= GetFrameTime();
        else if (timer != NULL && timer->lifetime < 0.f)
            timer->lifetime = 0.f;
    }
}

bool IsTimerDone(Timer* timer)
{
    if (timer != NULL)
        return (timer->lifetime <= 0.f);

    return false;
}
