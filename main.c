#include "src/engine.h"
#include "src/game.h"

int main(int argc, char* args[])
{
	//Init engine and game
	EngineInit("Game", 960, 540);//(320, 180 - 640, 360,
	GameInit(); 
	
	//--------------------------------------------------------
	// Main loop
	//--------------------------------------------------------
	while (EngineIsRunning()){
		EngineUpdate();
		GameUpdate();
		EngineRenderStart();
		GameDraw();
		EngineRenderEnd();
	}
	GameQuit();
	EngineQuit();
	return 0;
}
