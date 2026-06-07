#include "engine.h"

void EngineInit(const char* title, int w, int h) {
    WindowInitialize(w, h, title);
    ImageInit(WindowGetRenderer());
    // AudioInit is usually part of WindowInit
}

void EngineUpdate() {
    InputUpdate();   
    ClockTick(60);
}

void EngineRenderStart() {
    WindowClear();
}

void EngineRenderEnd() {
    WindowUpdate();
}

void EngineQuit() {
    ImageQuit();
    AudioQuit();
    WindowQuit();
    //Quit SDL subsystems
    //SDL_Quit(); <- it's called in WindowQuit();
}

bool EngineIsRunning() {
    return WindowIsRunning();
}