#include <SDL.h>
#include <assert.h>

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "config.h"

//System stuff
void WindowInitialize(unsigned short w, unsigned short h, const char * title);
void WindowQuit();
void WindowUpdate();
void WindowClear();
void WindowQuitMainLoop();
bool WindowIsRunning();
void WindowToggleFullscreen();
SDL_Renderer* WindowGetRenderer();

#endif