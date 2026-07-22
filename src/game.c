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

void GameInit(void) {
    // Initialize the master blueprint array
    EngineInit("Game", 960, 540);//(320, 180, "Game"); (640, 360, "Game");
    //DatabaseInit();
    DatabaseLoadAssets();
    
    EntityManagerInit();
    //init player first to be at index[0], so we can clear everything when changing rooms
    PlayerInit(10, 5);
    // Load initial map data
    LevelInit();
    ProjectileInit();
    VfxInit();

    // Set state
    currentState = STATE_GAMEPLAY;
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
        // Update Game Objects (AI, Animations, Life Cycles)
        EntityUpdateAll(dt);
        //update projectiles
        ProjectileUpdateAll(dt);
        
        VfxUpdateAll(dt);

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
                        ent->health -= p->damage;
                        VfxSpawn(p->pos, 512, 3);
                        AudioPlaySound(SND_HIT);
                        ent->hurtFrames = 12;
                        ent->knockbackDir = g_player->facingDir;
                        printf("ent id= %d \n", ent->id);
                        ProjectileDestroy(i);
                        break;
                    }
                }
            }
        }
        
        PlayerUpdate(dt);

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
        if (InputIsKeyPressed(SDL_SCANCODE_R)) {
            GameInit(); // reset
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

        LevelDraw(); //LevelDrawBackground();  // Layer 1 - Floors, Paths, Water
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


