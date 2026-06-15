#include "level.h"
#include "entity.h"

void LevelSave(const char* filename, int* map_data, int size) {
    FILE* file = fopen(filename, "wb");
    if (file != NULL) {
        fwrite(map_data, sizeof(int), size, file);
        fclose(file);
    }
}

void LevelLoad(const char* filename, int* map_data, int size) {
    FILE* file = fopen(filename, "rb");
    if (file != NULL) {
        fread(map_data, sizeof(int), size, file);
        fclose(file);
    }
}