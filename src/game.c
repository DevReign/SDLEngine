#include "game.h"
#include "engine.h"
#include "entity.h"
#include "level.h"
#include "data.h"
#include "player.h"
#include "projectile.h"
#include "vfx.h"
#include "hud.h"

static GameState currentState = STATE_TITLE;
static float levelChangeTimer = 0.0f;

void GameInit(void) {
    DatabaseLoadAssets();
    EntityManagerInit();
    //init player first to be at index[0], so we can clear everything when changing rooms. could also have isPlayer bool
    PlayerInit(10, 5);
    LevelInit("levels/0.bin");
    ProjectileInit();
    VfxInit();

    // Set state
    currentState = STATE_GAMEPLAY;
}

void GameRestart(void) {
    LevelSelectRoom(0);
    currentState = STATE_GAMEPLAY;
    g_player->health = g_player->data->maxHealth;
    g_player->frame = g_player->data->frameStart;
    g_player->playingAnim = true;
}

void GameUpdate(void) {
    float dt = ClockGetDeltaTime();
    if (InputIsKeyPressed(SDL_SCANCODE_ESCAPE)) WindowQuitMainLoop();
    if (InputIsKeyPressed(SDLK_q))
        WindowQuitMainLoop();
    if (InputIsKeyPressed(SDLK_l))
        WindowToggleFullscreen();

    switch (currentState) {
    case STATE_TITLE:
        if (InputIsKeyPressed(SDL_SCANCODE_RETURN)) {
            // Transition logic here
            currentState = STATE_GAMEPLAY;
        }
        break;

    case STATE_GAMEPLAY: {
        if (levelChangeTimer > 0)
            levelChangeTimer -= dt;

        // Update Game Objects (AI, Animations, Life Cycles)
        EntityUpdateAll(dt);
        ProjectileUpdateAll(dt);
        VfxUpdateAll(dt);

        unsigned short active_count_entity = EntityGetActiveCount();
        Entity* entity_pool = EntityGetPool();
        Entity* player = g_player;
        //Check collision for entities 
        for (int i = 0; i < active_count_entity; i++){
            Entity* a = &entity_pool[i];
            for (int j = i+1; j < active_count_entity; j++) {
                Entity* b = &entity_pool[j];
                
                //check for collision
                if (Vec2CheckRadiusOverlap(a->pos, 8, b->pos, 8)) {
                    if (a == g_player && b->eType == TYPE_PICKUP){
                        AudioPlaySound(SND_PICKUP);
                        if (a->health < a->data->maxHealth)
                            a->health += 15;
                        b->active = false;//EntityKill(b->id);
                        continue;
                    }
                    else if (a == g_player && b->eType == TYPE_SYSTEM) {
                        if (levelChangeTimer > 0)
                            continue;
                        if (b->eId == ENT_STAIRS_DOWN) {
                            AudioPlaySound(SND_STEP);
                            EntityClearAll();
                            LevelLoad("levels/1.bin");
                            LevelSelectRoom(LevelGetRoomId());
                            levelChangeTimer = 1.4f;
                        }
                        else if (b->eId == ENT_STAIRS_UP) {
                            AudioPlaySound(SND_STEP);
                            EntityClearAll();
                            LevelLoad("levels/0.bin");
                            LevelSelectRoom(LevelGetRoomId());
                            levelChangeTimer = 1.4f;
                        }
                    }
                }
            }
        }

        //put inactive at the end of the pool
        //needed until I fix swap-and-pop
        EntityCleanup();

        //Check collision for projectiles
        Projectile* proj_pool = ProjectileGetPool();
        for (int i = 0; i < ProjectileGetActiveCount(); i++) {
            Projectile* p = &proj_pool[i];
            if (!p->active) break;
            for (int t = 0; t < CHUNK_SIZE; t++) {
                if (LevelIsTileSolid(p->pos.x+p->radius, p->pos.y+ p->radius)) {
                    VfxSpawn(p->pos, 512, 3);
                    AudioPlaySound(SND_HIT);
                    ProjectileDestroy(i);
                    break;
                }
            }
            for (int e = 0; e < EntityGetActiveCount(); e++) {
                Entity* ent = EntityCheckCollisionByRadius(p->pos, p->radius);
                if (ent != nullptr) {
                    if (p->faction != ent->data->faction){
                        if (ent->eType == TYPE_CREATURE) {
                            ent->health -= p->damage;
                            VfxSpawn(p->pos, 512, 3);
                            AudioPlaySound(SND_HURT);
                            ent->hurtFrames = 16;
                            //TODO: lock direction to proj dir not the player
                            ent->knockbackDir = p->direction;
                            //printf("ent id= %d \n", ent->id);
                            ProjectileDestroy(i);
                            break;
                        }
                    }
                }
            }
        }
        
        PlayerUpdate(dt);

        //Game Over
        if (g_player->health < 1)
            currentState = STATE_GAMEOVER;

        //debug
        if (InputIsKeyPressed(SDLK_p)){
            printf("Debug: %f \n", ClockGetFps());
        }

        if (InputIsMousePressed(1)) {
            int mx, my;
            mx = 0;
            my = 0;
            SDL_GetMouseState(&mx, &my);
            // It's scale/2, wire up vars later
            printf("solid= %d \n", LevelGetTileId((mx + 3 / 2) / 3, (my + 3 / 2) / 3));
        }

        //change rooms
        //TODO: refactor and add actual player dimensions later. move to levelupdate?
        if (g_player->pos.x < 1){
            LevelSelectRoom(LevelFindAdjectId(3));
            ProjectileDestroyAll();
            g_player->pos.x = CHUNK_WIDTH * 16 - 18;
        }
        else if (g_player->pos.x+16 > CHUNK_WIDTH*16-2){
            LevelSelectRoom(LevelFindAdjectId(1));
            ProjectileDestroyAll();
            g_player->pos.x = 2;
        }
        else if (g_player->pos.y+16 > CHUNK_HEIGHT * 16-2){
            LevelSelectRoom(LevelFindAdjectId(2));
            ProjectileDestroyAll();
            g_player->pos.y = 2;
        }
        else if (g_player->pos.y < 1){
            LevelSelectRoom(LevelFindAdjectId(0));
            ProjectileDestroyAll();
            g_player->pos.y = CHUNK_HEIGHT * 16 - 18;
        }
    }
        
    case STATE_GAMEOVER:
        ImageDrawText(48, 120, TEX_GUI, "Game Over");
        if (InputIsKeyPressed(SDLK_r)) {
            GameRestart(); // reset
        }
        break;
    }
}

void GameDraw(void) {
    switch (currentState) {
    case STATE_TITLE:
        // Draw title background image or text
        ImageDrawText(64, 80, TEX_GUI, "Demon Knight");
        ImageDrawText(48, 120, TEX_GUI, "Press Enter to Start");
        break;

    case STATE_GAMEPLAY:

        LevelDraw();   // Layer 1 - Floors, Paths, Water
        EntityDrawAll();          // Layer 2 - Player, Enemies, Items (Y-Sorted?)
        ProjectileDrawAll();
        VfxDrawAll();
        //LevelDrawForeground();  // Layer 3 - Overhead door frames, tree tops
        HudDraw(0,152);              // Layer 4 - UI

        break;

    case STATE_GAMEOVER:
        ImageDrawText(96, 90, TEX_GUI, "GAME OVER");
        break;
    }
}

void GameQuit(void) {
    //LevelQuit();
    //EntityManagerQuit();
    //DataQuit();
}

GameState GameGetState(void) { return currentState; }
void GameSetState(GameState newState) { currentState = newState; }


