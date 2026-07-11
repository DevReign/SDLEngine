#include "projectile.h"
#include "entity.h"
#include "level.h"

static Projectile projectiles[MAX_PROJECTILES];
static activeCount = 0;

Projectile* ProjectileGetPool(void) {
	return projectiles;
}
int ProjectileGetActiveCount(void) {
	return activeCount;
}

void ProjectileInit() {
	SDL_memset(projectiles, 0, MAX_PROJECTILES);
}