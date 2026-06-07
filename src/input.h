#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include "config.h"
#include "Window.h"

//Input stuff
void InputUpdate();
bool InputCheckQuiting();
bool InputIsKeyPressed(uint8 k);
bool InputIsKeyHeld(uint8 k);
bool InputIsMousePressed(uint8 bttn);
bool InputIsMouseHeld(uint8 bttn);

#endif