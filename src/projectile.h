#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include <stdbool.h>

#define MAX_PROJECTILES 64

typedef struct {
	bool active;
	int width, height, spriteId, damage, fxId, sfxId;
	float x, y,vx ,vy;
	//int sourceX, sourceY; //for specific texture atlast coordinates
}Projectile;

Projectile* ProjectileGetPool(void);
int ProjectileGetActiveCount(void);
void ProjectileInit();
void ProjectileSpawn(int x, int y, int vx, int vy, );
void ProjectileDestroy();
#endif