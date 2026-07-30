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
		v->rate = 0.16f;
		v->lastFrame = f + num_frames;
		//v->loop = false;
		//v->radius = 8;
		//p->vel = vel;
		activeCount++;
	}
	return v;
}

void VfxDestroy(unsigned short i) {
		activeCount--;
		vfxPool[i] = vfxPool[activeCount];
		vfxPool[activeCount].active = false;
}

void VfxUpdateAll(float dt) {
	for (char i = activeCount - 1; i >= 0; i--) {
		//Animate
		vfxPool[i].frameTimer += dt;
		if (vfxPool[i].frameTimer > vfxPool[i].rate)
		{
			vfxPool[i].frameTimer -= vfxPool[i].rate;
			vfxPool[i].frame++;
			if (vfxPool[i].frame > vfxPool[i].lastFrame){
				VfxDestroy(i);
				break;
			}
		}

		//Move and destroy if it goes offscreen
		//vfxPool[i].pos = Vec2Add(vfxPool[i].pos, vfxPool[i].vel);
		if (vfxPool[i].pos.x > 256 || vfxPool[i].pos.x < -16 || vfxPool[i].pos.y > 240 || vfxPool[i].pos.y < 0) {
			VfxDestroy(i);
		}
		if (!vfxPool[i].active)
			VfxDestroy(i);
	}
}

void VfxDrawAll(void) {
	for (int i = 0; i < activeCount; i++) {
		Vfx* p = &vfxPool[i];

		ImageDrawTile(p->pos.x, p->pos.y, TEX_ATLAS, p->frame);
	}
}