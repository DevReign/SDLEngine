#include "player.h"
#include "engine.h"
#include "data.h"
#include "projectile.h"

PlayerProgress g_playerProgress = { 0 };

void PlayerInit(int gridX, int gridY) {
    g_playerProgress.keys = 0;
    g_playerProgress.hasSpeedBoots = false;
    g_playerProgress.maxHealthBonus = 0;

    g_player = EntitySpawn(gridX * TILE_SIZE, gridY * TILE_SIZE, ENT_PLAYER);
}

void PlayerUpdate(void) {
    if (g_player == NULL || g_player->id == 0) return;
    Vec2 dir;
    dir.x = 0;
    dir.y = 0;

    //TODO: make it so most recent direction overrides last using a queue
    if (InputIsKeyHeld(SDLK_a)){
        dir.x = -1;
        g_player->direction = 90;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_d)){
        dir.x = 1;
        g_player->direction = 270;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_w)){
        dir.y = -1;
        g_player->direction = 180;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_s)){
        dir.y = 1;
        g_player->direction = 0;
        //EntityAnimate(g_player);
    }

    //save last direction for attacks
    //TODO: maintain aim direction for attacks while button is held
    if(dir.x != 0 || dir.y != 0)// && !InputIsKeyHeld(SDLK_SPACE))
        g_player->lastDir = dir;

    EntityMoveWithCollision(g_player,dir);

    if (InputIsKeyPressed(SDLK_SPACE)) {
        ProjectileSpawn(g_player->pos, g_player->lastDir, PROJ_BULLET, FACTION_PLAYER);
    }

}
