#include "src/engine.h"
#include "src/game.h"

int main(int argc, char* args[])
{
	//Init engine and game
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
