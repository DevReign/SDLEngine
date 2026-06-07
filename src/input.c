#include "input.h"

static uint8 lastKey = '\0';
static bool pressedExit = false;
static bool mousePressed[4] = { 0 };
static bool mouseHeld[4] = { 0 };
static bool keyPressed[MAX_KEYS] = { 0 };
static bool keyHeld[MAX_KEYS] = { 0 };
static int mouseX, mouseY;
static SDL_Event events;

//Gets SDL's events and stores them in our struct to be used elsewhere.
void InputUpdate(){
	uint16 k = 0;
	uint8 b = 0;
	uint16 counter = 0;

	//Clear pressed keys
	SDL_memset(keyPressed, 0, MAX_KEYS);
	SDL_memset(mousePressed, 0, 4);
	lastKey = '\0';

	while (SDL_PollEvent(&events) != 0){
        k = events.key.keysym.sym;
        b = events.button.button;

        switch (events.type){
        case SDL_QUIT: WindowQuitMainLoop(); break;
        case SDL_KEYUP: keyHeld[k] = false; break;
        case SDL_KEYDOWN:

            keyHeld[k] = true;
            keyPressed[k] = true;
            if (k < MAX_KEYS)
                lastKey = (char)k;// (k < 127) ? (char)k : '\0';
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (b < 4){
                mouseHeld[b] = true;
                mousePressed[b] = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (b < 4)
                mouseHeld[b] = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mouseX, &mouseY);
            break;
        }
	}
}

bool InputCheckQuiting(){
	return pressedExit;
}

bool InputIsKeyPressed(uint8 k){
	if (keyPressed[k])
		return true;
	return false;
}

bool InputIsKeyHeld(uint8 k)
{
	if (keyHeld[k])
		return true;
	return false;
}

bool InputIsMousePressed(uint8 bttn)
{
	if (mousePressed[bttn])
		return true;
	return false;
}

bool InputIsMouseHeld(uint8 bttn)
{
	if (mouseHeld[bttn])
		return true;
	return false;
}

//Return mouse coordinates
SDL_Point InputGetMousePos()
{
	SDL_Point pos;
	pos.x = mouseX;
	pos.y = mouseY;
	return pos;
}