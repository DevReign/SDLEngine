#include "projectile.h"
#include "entity.h"
#include "level.h"

static Projectile projectiles[MAX_PROJECTILES];
static unsigned char activeCount = 0;

static Projectile projectileDatabase[PROJ_COUNT] = {
	{.faction = FACTION_ENEMY, .damage = 10, .radius = 8, .spriteId = 512, .vfxId = 0, .sfxId = 0 }
};

Projectile* ProjectileGetPool(void) {
	return projectiles;
}

int ProjectileGetActiveCount(void) {
	return activeCount;
}

void ProjectileInit() {
	SDL_memset(projectiles, 0, MAX_PROJECTILES);
}

Projectile * ProjectileSpawn(Vec2 pos, Vec2 vel, unsigned int type, Faction f) {
	Projectile* p = NULL;
	if (activeCount < MAX_PROJECTILES) {
		//printf("activeCount %d \n", activeCount);
		//projectiles[activeCount] = projectileDatabase[type];
		p = &projectiles[activeCount];
		*p = projectileDatabase[type];
		p->active = true;
		p->faction = f;
		p->pos.x = pos.x;
		p->pos.y = pos.y;
		p->vel = vel;
		activeCount++;
	}
	return p;
}

void ProjectileDestroy(unsigned short i) {
	if (i < activeCount && activeCount > 0) {
		activeCount--;
		projectiles[i] = projectiles[activeCount];
		projectiles[activeCount].active = false;
		printf("Projectile activeCount= %d \n", activeCount);
	}
}

void ProjectileDestroyAll(void) {
	SDL_memset(projectiles, 0, activeCount);
	activeCount = 0;
}

void ProjectileUpdateAll(void) {
	for (int i = 0; i < activeCount; i++) {
		if (!projectiles[i].active) break;
		projectiles[i].pos = Vec2Add(projectiles[i].pos, projectiles[i].vel);
		if (projectiles[i].pos.x > 256 || projectiles[i].pos.x < -16 || projectiles[i].pos.y > 240 || projectiles[i].pos.y < 0) {
			ProjectileDestroy(i); 
			break;
		}
	}
}

void ProjectileDrawAll(void) {
	for (int i = 0; i < activeCount; i++) {
		Projectile* p = &projectiles[i];
		if (!p->active) break;
		ImageDrawTile(p->pos.x, p->pos.y, TEX_ATLAS, p->spriteId);
	}
}