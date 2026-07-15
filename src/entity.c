#include "entity.h"
#include "level.h"

static Entity entities[MAX_ENTITIES] = { 0 };//static Entity *entityPool[64] = { 0 };
static unsigned short entityCount = 0;

Entity* g_player = NULL;
extern struct EntityBlueprint entityDatabase[ENT_COUNT];

void EntityManagerInit() {
	entityCount = 0;
	g_player = NULL;
	for (int i = 0; i < MAX_ENTITIES; ++i) {
		Entity * ent = &entities[i];
		ent->data = &entityDatabase[ENT_DUMMY];
		ent->pos.x = 0;
		ent->pos.y = 0;
		ent->health = ent->data->maxHealth;
		ent->frame = ent->data->frameStart;
		ent->id = 0;
		ent->animTimer = 0.14f;
	}
}

Entity* EntitySpawn(int x, int y, unsigned int eid) {
	//struct EntityBlueprint* dummyData = &entityDatabase[ENT_DUMMY];
	struct EntityBlueprint* spawnData = &entityDatabase[eid];

	for (int i = 0; i < MAX_ENTITIES; i++) {
		// check for the dummy blueprint
		if (entities[i].id == 0) {
			Entity* ent = &entities[i];

			// Wipe instance data block
			SDL_memset(ent, 0, sizeof(Entity));

			// Binds spawn properties
			ent->data = spawnData;
			ent->pos.x = x;
			ent->pos.y = y;
			ent->health = spawnData->maxHealth;
			ent->frame = spawnData->frameStart;
			ent->id = ++entityCount;
			ent->animTimer = 0.14f;

			return ent;
		}
	}
	return 0;
}


void EntityKill(Entity *e){
	if (e == NULL) return;
	SDL_memset(e, 0, sizeof(Entity));
	e->data = &entityDatabase[ENT_DUMMY];
}

//Don't clear player, so start at 1
void EntityClearAll() {
	for (int i = 1; i < MAX_ENTITIES; i++) {
		Entity* e = &entities[i];
		SDL_memset(e, 0, sizeof(Entity));
		e->data = &entityDatabase[ENT_DUMMY];
	}
	entityCount = 1;
}

void EntityDraw(Entity  *e){
	if (e->id==0)
		return;
	SDL_Point center = { 8, 8 };
	ImageDrawTileExt(e->pos.x, e->pos.y, TEX_ATLAS, e->frame, e->direction, &center, 0x00000000);
}

void EntityMove(Entity *e, Vec2 v){
	e->pos.x += v.x;
	e->pos.y += v.y;
}

void EntitySetPos(Entity *e, int px, int py){
	e->pos.x = px;
	e->pos.y = py;
}

void EntityAnimate(Entity *e){
	e->animTimer -= (float)ClockGetDeltaTime();
	int lastFrame = (e->data->frameStart + e->data->numFrames) - 1;

	if (e->frame < e->data->frameStart || e->frame > lastFrame)
	{
		e->frame = e->data->frameStart;
		e->animTimer = 0.14;
	}
	if (e->animTimer < 0)
	{
		e->animTimer += 0.14; // Add animation rate to entity data
		if (e->frame < lastFrame)
			e->frame += 1;
		else
			e->frame = e->data->frameStart;
	}
}

void EntityUpdateAll()
{
	Entity *e = 0;
	for (unsigned char i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i].id == 0) continue;

		e = &entities[i];
		switch (e->data->type)
		{
		case TYPE_CREATURE:
			EntityAnimate(e);
			switch (e->data->ai) {
			case AI_CHASE_PLAYER:
				if (e->pos.x < g_player->pos.x-16) e->pos.x += 1;
				if (e->pos.x > g_player->pos.x+16) e->pos.x -= 1;
				if (e->pos.y < g_player->pos.y-16) e->pos.y += 1;
				if (e->pos.y > g_player->pos.y+16) e->pos.y -= 1;
				break;
			}
			break;
		case TYPE_PROJECTILE:
			break;
		}		
	}
}

void EntityDrawAll()
{
	Entity *e = 0;
	SDL_Point center = { 8, 8 };
	for (unsigned char i = 0; i < MAX_ENTITIES; ++i) {
		if (entities[i].id < 1)
			continue;
		e = &entities[i];
		ImageDrawTileExt(e->pos.x, e->pos.y, TEX_ATLAS, e->frame, e->direction, &center, 0x00000000);
	}
}
Entity* EntityGetAtPoint(int px, int py) {
	Entity *e = 0;
	for (unsigned short i = 0; i < 32; ++i) {
		if (entities[i].id != 0){
			//if at the point
			return e;
		}
	}
	return e;
}

void EntityMoveWithCollision(Entity* e, Vec2 vel) {
	int width = e->data->width;
	int height = e->data->height;

	//X-axis
	for (int i = 0; i < abs(vel.x); i++) {
		int step_x = sign(vel.x);
		int next_x = step_x + e->pos.x;
		int check_x = (step_x > 0) ? next_x + width : next_x;
		bool ct = LevelIsTileSolid(check_x, e->pos.y);
		bool cb = LevelIsTileSolid(check_x, e->bottom);
		if (!ct && !cb) {
			e->pos.x += step_x;
			e->right = e->pos.x + width;
		}
		else {
			//Nudge player around tiles
			if (!ct && cb) {
				e->pos.y -= 1;
				e->bottom = e->pos.y + height;
				break;
			}
			else if (ct && !cb) {
				e->pos.y += 1;
				e->bottom = e->pos.y + height;
				break;
			}
			break;
		}
	}

	// Y-axis
	for (int i = 0; i < abs(vel.y); i++) {
		int step_y = sign(vel.y);
		int next_y = step_y + e->pos.y;
		int check_y = (step_y > 0) ? next_y + height : next_y;
		bool cl = LevelIsTileSolid(e->pos.x, check_y);
		bool cr = LevelIsTileSolid(e->right, check_y);

		if (!cl && !cr) {
			e->pos.y += step_y;
			e->bottom = e->pos.y + height;
		}
		else {
			//Nudge player around tiles
			if (!cl && cr) {
				e->pos.x -= 1;
				e->right = e->pos.x + width;
				break;
			}
			else if (cl && !cr) {
				e->pos.x += 1;
				e->right = e->pos.x + width;
				break;
			}
			break;
		}
	}
}