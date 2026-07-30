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
	}
}

void ProjectileKillIndex(int index) {
	if (activeCount == 0) return;
	activeCount--;
	projectiles[index] = projectiles[activeCount];
	projectiles[activeCount].active = false;
}

void ProjectileDestroyAll(void) {
	SDL_memset(projectiles, 0, activeCount);
	activeCount = 0;
}

void ProjectileUpdateAll(float dt) {
	for (short i = activeCount - 1; i >= 0; i--) {
		if (!projectiles[i].active) break;
		projectiles[i].pos = Vec2Add(projectiles[i].pos, projectiles[i].vel);
		if (projectiles[i].pos.x > 256 || projectiles[i].pos.x < -16 || projectiles[i].pos.y > 240 || projectiles[i].pos.y < 0) {
			ProjectileDestroy(i); 
			break;
		}
		if (!projectiles[i].active)
			EntityKillIndex(i);
	}
}
void ProjectileHandleAllCollisions(Entity* e_pool, int e_count) {
	Projectile* proj_pool = ProjectileGetPool();
	for (short i = activeCount - 1; i >= 0; i--) {
		Projectile* p = &proj_pool[i];

		if (LevelIsTileSolid(p->pos.x + p->radius, p->pos.y + p->radius)) {
			VfxSpawn(p->pos, 512, 3);
			AudioPlaySound(SND_HIT);
			ProjectileDestroy(i);
		}
		for (int j = 0; j < EntityGetActiveCount(); j++) {
			Entity* ent = &e_pool[j];
			if (Vec2CheckRadiusOverlap(p->pos, p->radius, ent->pos, 8))
			{
				if (ent != nullptr) {
					if (p->faction != ent->data->faction) {
						if (ent->eType == TYPE_CREATURE) {
							ent->health -= p->damage;
							VfxSpawn(p->pos, 512, 3);
							AudioPlaySound(SND_HURT);
							ent->hurtFrames = 16;
							//TODO: lock direction to proj dir not the player
							ent->knockbackDir = p->direction;
							//printf("ent id= %d \n", ent->id);
							ProjectileDestroy(i);
							break;
						}
					}
				}
			}
		}
	}
}
void ProjectileDrawAll(void) {
	for (int i = 0; i < activeCount; i++) {
		Projectile* p = &projectiles[i];

		ImageDrawTile(p->pos.x, p->pos.y, TEX_ATLAS, p->spriteId);
	}
}