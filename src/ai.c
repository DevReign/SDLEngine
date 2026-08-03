#include "level.h"
#include "vfx.h"
#include "ai.h"
//#include "entity.h"

void AIChaseMelee(Entity* e, float dt) {
	if (e->hurtFrames > 0) return;

	if (e->health < 1 && e->hurtFrames < 1) {
		//EntityKill(e->id);
		e->active = false;
		VfxSpawn(e->pos, 516, 4);
		EntitySpawn(e->pos.x, e->pos.y, ENT_SOUL);
		printf("Melee enemy died \n");
		AudioPlaySound(SND_DEATH);
	}
	
	if (!Vec2CheckRadiusOverlap(e->pos, 10,gPlayer->pos, 10)){
		// direction vector (Difference = Target - Source)
		/*Vec2 dir = Vec2Sub(gPlayer->pos, e->pos);
		float dist = Vec2Length(dir);
		e->vel.x = (dir.x/dist)* 2;
		e->vel.y = (dir.y/dist)* 2;*/

		if (e->pos.x < gPlayer->pos.x - 16) {
			e->vel.x += 1;
			e->facingDir = RIGHT;
		}
		else if (e->pos.x > gPlayer->pos.x + 16) {
			e->vel.x -= 1;
			e->facingDir = LEFT;
		}
		if (e->pos.y < gPlayer->pos.y - 16) {
			e->vel.y += 1;
			e->facingDir = DOWN;
		}
		else if (e->pos.y > gPlayer->pos.y + 16) {
			e->vel.y -= 1;
			e->facingDir = UP;
		}
		//EntityMoveWithCollision(e, e->vel);
	}

	//attack player
	if (e->attackTimer <= 0) {
		if (Vec2CheckRadiusOverlap(e->pos, 12, gPlayer->pos, 12)) {
			e->vel.x = 0.0f;
			e->vel.y = 0.0f;
			e->attackTimer = 0.80f;// e->data->attackSpeed;
			gPlayer->health -= 10;
			gPlayer->knockbackDir = e->facingDir;
			gPlayer->hurtFrames = 12;
			VfxSpawn(gPlayer->pos, 0, 1);
			if (gPlayer->health < 1) {
				gPlayer->frame = 286;
				gPlayer->playingAnim = false;
				AudioPlaySound(SND_DEATH);
			}
			else {
				AudioPlaySound(SND_HURT);
			}
		}
	}
	else {
		e->attackTimer -= dt;
	}
}