#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include <stdbool.h>

#define MAX_PROJECTILES 64

typedef enum {
	FACTION_ENEMY=0,
	FACTION_PLAYER,
	FACTION_NEUTRAL
} Faction;

typedef struct {
	bool active;
	Faction faction;
	int width, height, spriteId, damage, fxId, sfxId;
	float x, y,vx ,vy;
	//int sourceX, sourceY; //for specific texture atlast coordinates
}Projectile;

Projectile* ProjectileGetPool(void);
int ProjectileGetActiveCount(void);
void ProjectileInit();
void ProjectileSpawn(float x, float y, float vx, float vy, unsigned int type, Faction f);
void ProjectileDestroy(int index);
#endif