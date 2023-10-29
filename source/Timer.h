#pragma once

struct Timer
{
    float lifetime;
    bool hasStarted;
};

void ResetTimer(Timer* timer, float lifetime);
void StartTimer(Timer* timer, float lifetime);
void UpdateTimer(Timer* timer);
bool IsTimerDone(Timer* timer);
