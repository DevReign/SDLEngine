#include "player.h"
#include "engine.h"
#include "data.h"
#include "projectile.h"

PlayerProgress g_playerProgress = { 0 };
static float attackCoolDown = 0.0f;

void PlayerInit(int gridX, int gridY) {
    g_playerProgress.keys = 0;
    g_playerProgress.hasSpeedBoots = false;
    g_playerProgress.maxHealthBonus = 0;

    g_player = EntitySpawn(gridX * TILE_SIZE, gridY * TILE_SIZE, ENT_PLAYER);
}

void PlayerUpdate(float dt) {
    if (g_player == NULL || g_player->id == 0) return;
    Vec2 dir;
    dir.x = 0;
    dir.y = 0;

    //TODO: make it so most recent direction overrides last using a queue
    if (InputIsKeyHeld(SDLK_a)){
        dir.x = -1;
        g_player->direction = 90;
        g_player->facingDir = LEFT;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_d)){
        dir.x = 1;
        g_player->direction = 270;
        g_player->facingDir = RIGHT;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_w)){
        dir.y = -1;
        g_player->direction = 180;
        g_player->facingDir = UP;
        //EntityAnimate(g_player);
    }
    else if (InputIsKeyHeld(SDLK_s)){
        dir.y = 1;
        g_player->direction = 0;
        g_player->facingDir = DOWN;
        //EntityAnimate(g_player);
    }

    //save last direction for attacks
    //TODO: maintain aim direction for attacks while button is held
    if(dir.x != 0 || dir.y != 0)// && !InputIsKeyHeld(SDLK_SPACE))
        g_player->lastDir = dir;

    EntityMoveWithCollision(g_player,dir);

    if (attackCoolDown > 0){
        attackCoolDown -= dt;
    }

    if (InputIsKeyHeld(SDLK_SPACE) && attackCoolDown <= 0) {
        ProjectileSpawn(g_player->pos, Vec2Scale(g_player->lastDir, 2), PROJ_BULLET, FACTION_PLAYER);
        AudioPlaySound(SND_SHOOT);
        attackCoolDown = 0.32f;
        //printf("player facing dir %d \n", g_player->facingDir);
    }

}
