#include "game.h"
#include "engine.h"
#include "entity.h"
//#include "level.h"
#include "data.h"
#include "player.h"

static GameState currentState = STATE_TITLE;

void GameInit(void) {
    // Initialize the master blueprint array
    EngineInit("Game", 960, 540);//(320, 180, "Game"); (640, 360, "Game");
    //DatabaseInit();
    DatabaseLoadAssets();
    //LevelInit();
    EntityManagerInit();
    // Load initial map data
    //LevelLoad("0.bin");

    // Set state
    currentState = STATE_GAMEPLAY;

    if (currentState == STATE_GAMEPLAY) {
        //MapLoadRoom(7, 7);

        PlayerInit(8, 8);
        //Entity* zombie = EntitySpawn(96, 96, ENT_ZOMBIE);
    } 
}

void GameUpdate(void) {
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
        EntityUpdateAll(); //EntityManagerUpdate();

        //CollisionUpdate();

        // TODO: Check for Room Boundaries (Zelda Edge Detection)
        PlayerUpdate();

        if (InputIsKeyPressed(SDLK_p))
        {
            printf("Debug: %d \n", g_player->pos.x);
            printf("Debug: %d \n", g_player->pos.y);
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
        ImageDrawText(64, 80, TEX_GUI, "ZELDA MVP CLONE");
        ImageDrawText(48, 120, TEX_GUI, "PRESS ENTER TO START");
        break;

    case STATE_GAMEPLAY:
        //draw map
        for (uint16 r = 0; r < 12; ++r)
        {
            for (uint16 c = 0; c < 20; ++c)
            {
                ImageDrawTile(c * 16, r * 16, TEX_ATLAS, 68);
            }
        }
        
        //LevelDrawBackground();  // Layer 1 - Floors, Paths, Water
        EntityDrawAll();          // Layer 2 - Player, Enemies, Items (Y-Sorted?)
        //LevelDrawForeground();  // Layer 3 - Overhead door frames, tree tops
        //HUDDraw();              // Layer 4 - UI
        
        //Font test
        ImageDrawText(0, 0, TEX_GUI, "Testing ImageDrawText()!");
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


