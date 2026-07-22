#include "entity.h"
#include "level.h"
#include "vfx.h"

static Entity entities[MAX_ENTITIES] = { 0 };//static Entity *entityPool[64] = { 0 };
static unsigned short entityCount = 0;
static unsigned short activeCount = 0;
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
	struct EntityBlueprint* spawnData = &entityDatabase[eid];

	if (activeCount < MAX_ENTITIES) {
		Entity* ent = &entities[activeCount];
		printf("Spawn entityCount= %d \n", entityCount);
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
		ent->active = true;
		activeCount++;
		return ent;
	}
	return nullptr;
}


void EntityKill(int id){
	//if (id < activeCount && activeCount > 0) {
	for (int i = 0; i < activeCount; i++){
		if (entities[i].id == id) {
			activeCount--;
			entities[i] = entities[activeCount];
		}
	}
}

void EntityClearAll() {
	//Don't clear player, so start at 1
	for (int i = 1; i < activeCount; i++) {
		entities[i].active = false;
	}
	activeCount = 1;
}

unsigned int EntityGetActiveCount() {
	return activeCount;
}

Entity* EntityCheckCollisionByRadius(Vec2 v, int r) {
	for (int i = 0; i < activeCount; i++) {
		unsigned char ent_r = entities[i].data->radius;
		//TODO: use width and height later, but radius for now
		float dx = (entities[i].pos.x + ent_r) - (v.x + r);
		float dy = (entities[i].pos.y + ent_r) - (v.y + r);
		float dist = dx*dx + dy*dy;
		unsigned short radius = ent_r + r;
		if ((dist) < (radius* radius))
			return &entities[i];
	}
	return nullptr;
}

Entity* EntityGetById(int id) {
	for (int i = 0; i < activeCount; i++) {
		if (entities[i].id == id)
			return &entities[i];
	}
	return NULL;
}

void EntityDraw(Entity  *e){
	if (e->hurtFrames > 0) {
		e->hurtFrames -= 0.016;// move to update?
		if ((int)e->hurtFrames *10 % 2==0)
			return;
	}
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

	if (e->frame < e->data->frameStart || e->frame > lastFrame){
		e->frame = e->data->frameStart;
		e->animTimer = 0.14;
	}
	if (e->animTimer < 0){
		e->animTimer += 0.14; // Add animation rate to entity data
		if (e->frame < lastFrame)
			e->frame += 1;
		else
			e->frame = e->data->frameStart;
	}
}

void EntityUpdateAll(float dt){
	for (unsigned char i = 0; i < activeCount; ++i){
		if (!entities[i].active) continue;

		Entity* e = &entities[i];
		switch (e->data->type){
		case TYPE_CREATURE:
			EntityAnimate(e);
			switch (e->data->ai) {
			case AI_CHASE_PLAYER:
				if (e->health < 1) {
					EntityKill(e->id);
					VfxSpawn(e->pos, 516, 4);
				}
				if (e->hurtFrames > 0) {
					e->hurtFrames--;
					
					switch (e->knockbackDir) {
					case UP:    e->pos.y -= 2; break;// speed * deltaTime; break;
					case DOWN:  e->pos.y += 2; break;
					case LEFT:  e->pos.x -= 2; break;
					case RIGHT: e->pos.x += 2; break;
					}
					break;
				}
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

void EntityDrawAll() {
	Entity *e = 0;
	SDL_Point center = { 8, 8 };
	for (unsigned char i = 0; i < activeCount; ++i) {
		if (!entities[i].active) continue;

		e = &entities[i];
		if (e->hurtFrames > 0) {
			if (e->hurtFrames % 3 == 0) continue;
		}
		ImageDrawTileExt(e->pos.x, e->pos.y, TEX_ATLAS, e->frame, e->direction, &center, 0x00000000);
	}
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