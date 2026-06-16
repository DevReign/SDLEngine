#include "level.h"
#include "entity.h"

static int tileData[ARRAY_SIZE];
static int objectData[ARRAY_SIZE];

void LevelSave(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(tileData, sizeof(int), ARRAY_SIZE, file);
        fclose(file);
    }
}

void LevelLoad(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        fread(tileData, sizeof(int), ARRAY_SIZE, file);
        fread(objectData, sizeof(int), ARRAY_SIZE, file);
        fclose(file);
    }
}
void LevelDraw() {
    int i = 0;
    for (int r = 0; r < CHUNK_HEIGHT;  r++){
        for (int c = 0; c < CHUNK_WIDTH; c++){
            i = tileData[r * CHUNK_WIDTH + c];
            // add 40 to center the map for now
            ImageDrawTile(c * 16+ 40, r * 16, TEX_ATLAS, i);
        }
    }
}
short LevelInit() {
    SDL_memset(tileData, 0, ARRAY_SIZE);
    SDL_memset(objectData, 0, ARRAY_SIZE);
    LevelLoad("0.bin");
}
