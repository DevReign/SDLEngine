#ifndef VFX_H
#define VFX_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "vector.h"
#include "data.h"

#define MAX_VFX 64

typedef struct {
	bool active;// , loop;
	//unsigned char radius;//just used for centering 
	Vec2 pos;//vel
	int frame, lastFrame; //sourceX, sourceY; //for specific texture atlast coordinates
	float frameTimer, rate;
}Vfx;

Vfx* VfxGetPool(void);
int VfxGetActiveCount(void);
void VfxInit();
Vfx* VfxSpawn(Vec2 pos, int f, int num_frames);// Vec2 vel, unsigned int type, Faction f);
void VfxDestroy(unsigned short i);
void VfxUpdateAll(float dt);
void VfxDrawAll(void);
#endif