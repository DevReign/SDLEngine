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

void LevelSave(const char* filename);
void LevelLoad(const char* filename);
void LevelDraw();
short LevelInit();
#endif
