#pragma once

struct Timer
{
    float lifetime;
    bool hasStarted;
};

void StartTimer(Timer* timer, float lifetime);
void UpdateTimer(Timer* timer);
bool IsTimerDone(Timer* timer);
