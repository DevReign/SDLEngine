#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "data.h"

#define MAX_ENTITIES 32
#define GET_CENTER_X ((Entity).x + ((Entity).width/2))
#define GET_CENTER_Y ((Entity).y + ((Entity).height/2))

typedef struct tagEntity{
	unsigned short id; //unique entity id
	unsigned short health;
	Vec2 pos, vel, lastDir;
	struct EntityBlueprint *data;
	bool invulnerable;
	bool playingAnim;
	unsigned char state;
	unsigned short frame, direction;
	float attackTimer, animTimer, flinchTimer;
	int right, bottom;
} Entity;

extern Entity* g_player;

void EntityManagerInit();
void EntityDraw(Entity *e);
void EntityMove(Entity *e, Vec2 v);
void EntitySetPos(Entity *e, int px, int py);
void EntityAnimate(Entity* e);
//bool EntityCollide();
Entity *EntitySpawn(int x, int y, unsigned int eid);
void EntityKill(Entity *e);
void EntityClearAll();
void EntityUpdateAll();
void EntityDrawAll();
//void EntityQuit() {};
void EntityMoveWithCollision(Entity* e, Vec2 vel);

#endif
