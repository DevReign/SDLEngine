#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "data.h"

#define MAX_ENTITIES 32
#define GET_CENTER_X ((Entity).x + ((Entity).width/2))
#define GET_CENTER_Y ((Entity).y + ((Entity).height/2))

typedef struct{
	bool active, invulnerable, playingAnim;
	unsigned char state, facingDir, knockbackDir, hurtFrames;
	short id, health, frame, direction;
	struct EntityBlueprint *data;
	Vec2 pos, vel, lastDir;
	int right, bottom;
	float attackTimer, animTimer;// knockbackTimer, hurtTimer, flinchTimer;
} Entity;

extern Entity* g_player;

void EntityManagerInit();
Entity * EntityGetById(int id);
Entity * EntityCheckCollisionByRadius(Vec2 v, int r);
unsigned int EntityGetActiveCount();
void EntityDraw(Entity *e);
void EntityMove(Entity *e, Vec2 v);
void EntitySetPos(Entity *e, int px, int py);
void EntityAnimate(Entity* e);
//bool EntityCollide();
Entity * EntitySpawn(int x, int y, unsigned int eid);
void EntityKill(int id);
void EntityClearAll();
void EntityUpdateAll(float dt);
void EntityDrawAll();
//void EntityQuit() {};
void EntityMoveWithCollision(Entity* e, Vec2 vel);

#endif
