#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "vector.h"

#define MAX_PROJECTILES 64

typedef enum {
	FACTION_ENEMY=0,
	FACTION_PLAYER,
	FACTION_NEUTRAL
} Faction;

typedef enum {
	PROJ_BULLET = 0,
	PROJ_COUNT
} ProjectileId;

typedef struct {
	bool active;
	Faction faction;
	int width, height, spriteId, damage, vfxId, sfxId;
	Vec2 pos, vel;
	//float vx ,vy;
	//int sourceX, sourceY; //for specific texture atlast coordinates
}Projectile;

Projectile* ProjectileGetPool(void);
int ProjectileGetActiveCount(void);
void ProjectileInit();
void ProjectileSpawn(Vec2 pos, Vec2 vel, unsigned int type, Faction f);
void ProjectileDestroy(int index);
Projectile* ProjectileUpdate(int i);
void ProjectileDrawAll(void);
#endif