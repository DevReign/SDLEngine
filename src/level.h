#ifndef LEVEL_H
#define LEVEL_H

#include "config.h"
#include <stdbool.h>
#include <stdint.h>

#define LEVEL_KEY "RAM0"
#define LEVEL_KEY_SIZE 4
#define LEVEL_CURRENT_VERSION 1

void LevelSave(const char* filename, int* map_data, int size);
void LevelLoad(const char* filename, int* map_data, int size);

#endif
