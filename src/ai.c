#include "level.h"
#include "vfx.h"
#include "ai.h"
//#include "entity.h"

void AIChaseMelee(Entity* e, float dt) {
	if (e->health < 1) {
		EntityKill(e->id);
		VfxSpawn(e->pos, 516, 4);
	}

	//move toward player
	if (e->pos.x < g_player->pos.x - 16) {
		e->pos.x += 1;
		e->facingDir = RIGHT;
	}
	if (e->pos.x > g_player->pos.x + 16) {
		e->pos.x -= 1;
		e->facingDir = LEFT;
	}
	if (e->pos.y < g_player->pos.y - 16) {
		e->pos.y += 1;
		e->facingDir = DOWN;
	}
	if (e->pos.y > g_player->pos.y + 16) {
		e->pos.y -= 1;
		e->facingDir = UP;
	}
	//attack player
	if (e->attackTimer <= 0) {
		if (Vec2CheckRadiusOverlap(e->pos, 9, g_player->pos, 9)) {
			e->attackTimer = 0.80f;// e->data->attackSpeed;
			AudioPlaySound(SND_HIT);
			g_player->health -= 10;
			g_player->knockbackDir = e->facingDir;
			g_player->hurtFrames = 12;
			VfxSpawn(g_player->pos, 0, 1);
			if (g_player->health < 1) {
				g_player->frame = 286;
				g_player->playingAnim = false;
			}
		}
	}
	else {
		e->attackTimer -= dt;
	}
}