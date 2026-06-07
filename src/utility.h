#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define UtilToggleBool(b) ((b) = !(b))

void UtilStringCopy(char* dest, const char* src, size_t dest_size);
//bool UtilPointInRect(int px, int py, const SDL_Rect* r) {
//    SDL_Point p = { px, py };
//    return SDL_PointInRect(&p, r);
//}

#endif