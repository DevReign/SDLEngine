#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "config.h"

struct TileSheet
{
	SDL_Texture* texture;
	uint16 tileWidth;
	uint16 tileHeight;
	uint16 width;
	uint16 height;
};

void ImageInit(SDL_Renderer* r);
void ImageLoadTilesheet(const char * filename, unsigned short id, unsigned short w, unsigned short h);
void ImageDraw(int x, int y, unsigned short img_id);
void ImageDrawTile(int x, int y, unsigned short img_id, short sub_id);
void ImageDrawTileExt(int x, int y, unsigned short img_id, short sub_id, double angle, SDL_Point* center, SDL_RendererFlip flip);
void ImageDrawText(int x, int y, unsigned short img_id, const char * text);
void ImageQuit();

#endif