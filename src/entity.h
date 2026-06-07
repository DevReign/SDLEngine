#ifndef ENTITY_H
#define ENTITY_H

#include "engine.h"
#include "data.h"

#define MAX_ENTITIES 64

typedef struct tagEntity{
	uint16 id; //unique entity id
	uint16 health;
	Vec2 pos;
	struct EntityBlueprint *data;
	bool invulnerable;
	bool playingAnim;
	uint8 state;
	uint16 frame, direction;
	float attackTimer, animTimer, flinchTimer;
	signed int left, top, right, bottom;
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
void EntityUpdateAll();
void EntityDrawAll();
//void EntityQuit() {};

#endif
