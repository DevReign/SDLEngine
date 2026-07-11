#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "input.h"
#include "audio.h"
#include "image.h"
#include "clock.h"
#include "config.h"

#define sign(x) ((x>0)-(x<0))

// High-level engine controls
void EngineInit(const char* title, int w, int h);
void EngineUpdate(); // Handles input and clock
void EngineRenderStart(); // Clears screen
void EngineRenderEnd(); // Presents to screen
void EngineQuit();
bool EngineIsRunning();

#endif
