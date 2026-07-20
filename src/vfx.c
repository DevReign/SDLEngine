#include "vfx.h"

static Vfx vfxPool[MAX_VFX];
static unsigned char activeCount = 0;

Vfx* VfxGetPool(void) {
	return vfxPool;
}

int VfxGetActiveCount(void) {
	return activeCount;
}

void VfxInit() {
	SDL_memset(vfxPool, 0, MAX_VFX);
}

Vfx * VfxSpawn(Vec2 pos, int f, int num_frames) {
	Vfx* v = NULL;
	if (activeCount < MAX_VFX) {
		//printf("activeCount %d \n", activeCount);
		v = &vfxPool[activeCount];
		v->active = true;
		v->pos.x = pos.x;
		v->pos.y = pos.y;
		v->frame = f;
		v->numFrames = num_frames;
		v->lastFrame = f + num_frames;
		v->loop = false;
		v->radius = 8;
		//p->vel = vel;
		activeCount++;
	}
	return v;
}

void VfxDestroy(unsigned short i) {
	if (i < activeCount && activeCount > 0) {
		activeCount--;
		vfxPool[i] = vfxPool[activeCount];
		vfxPool[activeCount].active = false;
		//printf("activeCount %d \n", activeCount);
	}
}

void VfxUpdateAll(float dt) {
	for (int i = 0; i < activeCount; i++) {
		if (!vfxPool[i].active)
			break;

		vfxPool[i].frameTimer += dt;
		if (vfxPool[i].frameTimer > 0.15f)
		{
			vfxPool[i].frameTimer -= 0.15f;
			vfxPool[i].frame++;
			if (vfxPool[i].frame > vfxPool[i].lastFrame){
				printf("vfx activeCount= %d \n", activeCount);
				VfxDestroy(i);
				break;
			}
		}
		//if (!vfxPool[i].active) break;
		//vfxPool[i].pos = Vec2Add(vfxPool[i].pos, vfxPool[i].vel);
		if (vfxPool[i].pos.x > 256 || vfxPool[i].pos.x < -16 || vfxPool[i].pos.y > 240 || vfxPool[i].pos.y < 0) {
			VfxDestroy(i);
		}
	}
}

void VfxDrawAll(void) {
	for (int i = 0; i < activeCount; i++) {
		Vfx* p = &vfxPool[i];
		if (!p->active) break;

		ImageDrawTile(p->pos.x, p->pos.y, TEX_ATLAS, p->frame);
	}
}