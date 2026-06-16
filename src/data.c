#include "data.h"

void DatabaseLoadAssets(void) {
    // Load Graphic Atlas Sheets
    ImageLoadTilesheet("images/atlas.bmp", TEX_ATLAS, 16, 16);
    ImageLoadTilesheet("images/gui.bmp", TEX_GUI, 8, 8);

    // Music & Sounds
    AudioLoadMusic("audio/Retroloop.ogg");
    AudioLoadSound("audio/bfxrHit.ogg", SND_HIT);

    // Configure
    AudioSetVolume(10);
    //AudioPlayMusic();
}

struct EntityBlueprint entityDatabase[ENT_COUNT] = {
    // ENT_DUMMY
    {
        .type = TYPE_STATIC, .ai = AI_NONE,
        .maxHealth = 0, .touchDamage = 0, .speed = 0,
        .width = 16, .height = 16, .rotateSprite = false,
        .projectileId = 0, .frameStart = 0, .frameAttack = 0, .numFrames = 0, .animRate = 0.0f
    },
    // ENT_PLAYER
    {
        .type = TYPE_CREATURE, .ai = AI_NONE,
        .maxHealth = 100, .touchDamage = 0, .speed = 2,
        .width = 12, .height = 12, .rotateSprite = false, // Slightly smaller hitbox for forgiving collisions
        .projectileId = 0, .frameStart = 0, .frameAttack = 8, .numFrames = 4, .animRate = 0.12f
    },
    // ENT_ZOMBIE
    {
        .type = TYPE_CREATURE, .ai = AI_CHASE_PLAYER,
        .maxHealth = 30, .touchDamage = 10, .speed = 1,
        .width = 14, .height = 14, .rotateSprite = false,
        .projectileId = 0, .frameStart = 16, .frameAttack = 16, .numFrames = 4, .animRate = 0.16f
    }
};

/*
* old method
// type,maxHealth,damage,speed,attackSpeed,ai,width,height,rotateSprite,projectileId, frameStart,frameAttack,frameOffset,numFrames;
static struct EntityBlueprint entityBlueprint[] =
{
	// Dummy Object
	TYPE_STATIC, 0, 0, 0, 0, AI_NONE, 0, 0, 0, 0, 0, 0, 0, 0,
	// Player
	TYPE_CREATURE, 100, 10, 1, 1, AI_NONE, 16, 16, 1, 0, 0, 4, 0, 3,
	// Zombie
	TYPE_CREATURE, 25, 25, 1, 1, AI_CHASE_PLAYER, 16, 16, 1, 0, 16, 4, 0, 3
};*/