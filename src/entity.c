#include "entity.h"
#include "level.h"

static Entity entities[MAX_ENTITIES] = { 0 };//static Entity *entityPool[64] = { 0 };
static uint16 entityCount = 0;

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
	struct EntityBlueprint* dummyData = &entityDatabase[ENT_DUMMY];
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

void EntityDraw(Entity  *e){
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
	for (uint8 i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i].id == 0) continue;

		e = &entities[i];
		switch (e->data->type)
		{
		case TYPE_CREATURE:
			switch (e->data->ai) {
			case AI_CHASE_PLAYER:
				if (e->pos.x < g_player->pos.x) e->pos.x += 1;
				if (e->pos.x > g_player->pos.x) e->pos.x -= 1;
				if (e->pos.y < g_player->pos.y) e->pos.y += 1;
				if (e->pos.y > g_player->pos.y) e->pos.y -= 1;
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
	for (uint8 i = 0; i < 32; ++i) {
		if (entities[i].id == 0) continue;
		e = &entities[i];
		ImageDrawTileExt(e->pos.x, e->pos.y, TEX_ATLAS, e->frame, e->direction, &center, 0x00000000);
	}
}
Entity* EntityGetAtPoint(int px, int py) {
	Entity *e = 0;
	for (uint16 i = 0; i < 32; ++i) {
		if (entities[i].id != 0){
			//if at the point
			return e;
		}
	}
	return e;
}