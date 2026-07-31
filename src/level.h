#ifndef LEVEL_H
#define LEVEL_H

#include "config.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#define CHUNK_WIDTH 15
#define CHUNK_HEIGHT 9
#define CHUNK_SIZE CHUNK_WIDTH*CHUNK_HEIGHT
#define LEVEL_WIDTH 8
#define LEVEL_HEIGHT 8
#define LEVEL_SIZE LEVEL_HEIGHT*LEVEL_WIDTH
#define ARRAY_SIZE CHUNK_SIZE*LEVEL_SIZE

typedef enum {
	TILE_FLAG_GROUND = 0,
	TILE_FLAG_LOW = 1, // pit or water collision
	TILE_FLAG_MID = 2, // rocks and decos
	TILE_FLAG_HIGH = 4,// unpassable, like walls
	TILE_FLAG_ANIM = 8,
	TILE_FLAG_WATER = 16,
	TILE_FLAG_DOT = 32 // does dmg over time
}TileFlags;

void LevelSave(const char* filename);
void LevelLoad(const char* filename);
void LevelSelectRoom(int id);
int LevelGetRoomId(void);
void LevelDraw(float dt);
void LevelInit(const char* level);
short LevelFindAdjectId(short dir);
char LevelIsTileSolid(int x, int y);
short LevelGetTileId(int x, int y);
#endif
