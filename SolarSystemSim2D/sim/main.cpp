/*
main.cpp

Description
-----------
Run the solar system simulation.
*/

#define SDL_MAIN_HANDLED
#include "SolarSystem.h"

int main(int argc, char* argv) {
	SDL_SetMainReady();

	SolarSystemEngine engine;
	bool initialized = engine.initialize();

	if (initialized) {
		engine.runSimulation();
	}

	engine.shutdown();

	return 0;
}