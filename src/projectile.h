#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "vector.h"
#include "data.h"

#define MAX_PROJECTILES 64

typedef enum {
	PROJ_BULLET = 0,
	PROJ_COUNT
} ProjectileId;

typedef struct {
	bool active;
	unsigned char radius, damage, vfxId, sfxId;//width, height,
	Faction faction;
	Vec2 pos, vel;
	int spriteId; //sourceX, sourceY; //for specific texture atlast coordinates
}Projectile;

Projectile* ProjectileGetPool(void);
int ProjectileGetActiveCount(void);
void ProjectileInit();
Projectile * ProjectileSpawn(Vec2 pos, Vec2 vel, unsigned int type, Faction f);
void ProjectileDestroy(unsigned short i);
void ProjectileUpdateAll(void);
void ProjectileDrawAll(void);
#endif