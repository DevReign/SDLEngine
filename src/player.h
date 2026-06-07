#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "entity.h"


// Unified state tracker for inventory and upgrades
typedef struct {
    // Items
    uint8_t  keys;
    // Upgrades / Progression Flags
    bool     hasSpeedBoots;
    // Stat Modifiers
    int      maxHealthBonus;
} PlayerProgress;

// Global Access to Player State
extern PlayerProgress g_playerProgress;

// Execution Control Loops called by game.c
void PlayerInit(int gridX, int gridY);
void PlayerUpdate(void);
//void PlayerRender(void);

#endif
