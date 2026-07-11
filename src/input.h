#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "config.h"
#include "Window.h"

#define MAX_KEYS 512

//Input stuff
void InputUpdate();
bool InputCheckQuiting();
bool InputIsKeyPressed(unsigned char k);
bool InputIsKeyHeld(unsigned char k);
bool InputIsMousePressed(unsigned char bttn);
bool InputIsMouseHeld(unsigned char bttn);
SDL_Point InputGetMousePos();
int InputGetMouseX();
int InputGetMouseY();
#endif