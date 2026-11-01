/*
main.cpp

Description
-----------
Runs the game loop.
SDL_MAIN_HANDLED and SDL_SetMainReady avoid SDL from renaming the standard main()
function to SDL_main().

Reference
---------
Chapter 1: Game Loop and Game Class
Game Programming in C++ - Sanjav Madhav
*/

#define SDL_MAIN_HANDLED
#include "Game.h"

int main(int argc, char** argv) {
	SDL_SetMainReady();

	Game game;
	bool initialized = game.initialize();

	if (initialized) {
		game.run_loop();
	}

	game.shutdown();
	game.display_score();

	return 0;
}