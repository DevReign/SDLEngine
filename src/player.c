#include "player.h"
#include "engine.h"
#include "data.h"

PlayerProgress g_playerProgress = { 0 };

void PlayerInit(int gridX, int gridY) {
    g_playerProgress.keys = 0;
    g_playerProgress.hasSpeedBoots = false;
    g_playerProgress.maxHealthBonus = 0;

    g_player = EntitySpawn(gridX * TILE_SIZE, gridY * TILE_SIZE, ENT_PLAYER);
}

void PlayerUpdate(void) {
    if (g_player == NULL || g_player->id == 0) return;
    
    if (InputIsKeyHeld(SDLK_a))
    {
        g_player->pos.x -= 1;
        g_player->direction = 90;
        EntityAnimate(g_player);
    }
    if (InputIsKeyHeld(SDLK_d))
    {
        g_player->pos.x += 1;
        g_player->direction = 270;
        EntityAnimate(g_player);
    }
    if (InputIsKeyHeld(SDLK_w))
    {
        g_player->pos.y -= 1;
        g_player->direction = 180;
        EntityAnimate(g_player);
    }
    if (InputIsKeyHeld(SDLK_s))
    {
        g_player->pos.y += 1;
        g_player->direction = 0;
        EntityAnimate(g_player);
    }

    if (InputIsKeyPressed(SDLK_SPACE)) {
    }
}
