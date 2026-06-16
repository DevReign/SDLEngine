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
            ImageDrawTile(c * 16, r * 16, TEX_ATLAS, i);
        }
    }
}
short LevelInit() {
    SDL_memset(tileData, 0, ARRAY_SIZE);
    SDL_memset(objectData, 0, ARRAY_SIZE);
    LevelLoad("0.bin");
}

/*int load_raw_room_data(const char* filename) {

    FILE* file = fopen(filename, "rb");

    if (!file){

        printf("Error: Could not open raw map file: %s\n", filename);
        return 0;
    }

    size_t tiles_read = fread(out_room->tiles, sizeof(int), ROOM_HEIGHT * ROOM_WIDTH, file);
    size_t entities_read = fread(out_room->entities, sizeof(int), ROOM_HEIGHT * ROOM_WIDTH, file);

    fclose(file);

    int expected_elements = ROOM_HEIGHT * ROOM_WIDTH;

    if (tiles_read != expected_elements || entities_read != expected_elements) {

        printf("Warning: Map file data mismatch.\n");
        return 0;
    }
    return 1;
}*/