/*
main.cpp

Description
-----------
Creates the simulation and runs the main loop.
SDL_MAIN_HANDLED and SDL_SetMainReady prevent SDL from renaming
the standard main() to SDL_main().
*/

#define SDL_MAIN_HANDLED
#include "Orbit.h"

int main(int argc, char** argv) {
	SDL_SetMainReady();

	Orbit2D orbit_sim;
	bool initialized = orbit_sim.initialize();

	if (initialized) {
		orbit_sim.runSimulationLoop();
	}

	orbit_sim.shutdown();

	return 0;
}