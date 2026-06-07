#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>

//clock stuff
void ClockInit();
double ClockGetTime();
float ClockGetDeltaTime();
void ClockTick(float d_fps);

#endif