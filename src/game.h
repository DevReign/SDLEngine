#ifndef GAME_H
#define GAME_H
#include "game.h"
//#include "hud.h"
//#include "map.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

typedef enum {
    STATE_TITLE,
    STATE_GAMEPLAY,
    STATE_GAMEOVER
} GameState;

// Interface called by main.c
void GameInit(void);
void GameUpdate(void);
void GameDraw(void);
void GameQuit(void);

// Global state getters
GameState GameGetState(void);
void GameSetState(GameState newState);

#endif
