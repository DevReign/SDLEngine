#include "projectile.h"
#include "entity.h"
#include "level.h"

static Projectile projectiles[MAX_PROJECTILES];
static activeCount = 0;

static Projectile projectileDatabase[PROJ_COUNT] = {
	{.faction = FACTION_ENEMY, .radius = 8, .spriteId = 0, .vfxId = 0, .sfxId = 0 }
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
	if (activeCount < MAX_PROJECTILES) {
		//projectiles[activeCount] = projectileDatabase[type];
		Projectile* p = &projectiles[activeCount];
		*p = projectileDatabase[type];
		p->active = true;
		p->faction = f;
		p->pos.x = pos.x;
		p->pos.y = pos.y;
		p->vel = vel;
		activeCount++;
	}
}

void ProjectileDestroy(int i) {
	if (i >= 0 && i < activeCount)
		activeCount--;
		projectiles[i] = projectiles[activeCount];
		projectiles[activeCount].active = false;
}

void ProjectileUpdateAll(void) {
	for (int i = 0; i < activeCount; i++) {
		if (projectiles[i].pos.x > 256 || projectiles[i].pos.x < -16 || projectiles[i].pos.y > 240 || projectiles[i].pos.y < 0) {
			ProjectileDestroy(i);
			return nullptr;
		}
		projectiles[i].pos = Vec2Add(projectiles[i].pos, projectiles[i].vel);
	}
}

void ProjectileDrawAll(void) {
	for (int i = 0; i < activeCount; i++) {
		Projectile* p = &projectiles[i];
		ImageDrawTile(p->pos.x, p->pos.y, TEX_ATLAS, p->spriteId);
	}
}