#include "input.h"

static unsigned char lastKey = '\0';
static bool pressedExit = false;
static bool mousePressed[4] = { 0 };
static bool mouseHeld[4] = { 0 };
static bool keyPressed[MAX_KEYS] = { 0 };
static bool keyHeld[MAX_KEYS] = { 0 };
static int mouseX, mouseY;
static SDL_Event events;

//Gets SDL's events and stores them in our struct to be used elsewhere.
void InputUpdate(){
	unsigned short k = 0;
	unsigned char b = 0;
	unsigned short counter = 0;

	//Clear pressed keys
	SDL_memset(keyPressed, 0, MAX_KEYS);
	SDL_memset(mousePressed, 0, 4);
	lastKey = '\0';

	while (SDL_PollEvent(&events) != 0){
        k = events.key.keysym.sym;
        b = events.button.button;

        switch (events.type){
		case SDL_QUIT: printf("Pressed quit"); WindowQuitMainLoop(); break;
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

bool InputIsKeyPressed(unsigned char k){
	if (keyPressed[k])
		return true;
	return false;
}

bool InputIsKeyHeld(unsigned char k){
	if (keyHeld[k])
		return true;
	return false;
}

bool InputIsMousePressed(unsigned char bttn){
	if (mousePressed[bttn])
		return true;
	return false;
}

bool InputIsMouseHeld(unsigned char bttn){
	if (mouseHeld[bttn])
		return true;
	return false;
}

//Return mouse coordinates
SDL_Point InputGetMousePos(){
	SDL_Point pos;
	pos.x = mouseX;
	pos.y = mouseY;
	return pos;
}
int InputGetMouseX() { return mouseX; }
int InputGetMouseY() { return mouseY; }