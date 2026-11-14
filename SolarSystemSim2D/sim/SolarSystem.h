/**
SolarSystem.h

Description
-----------
Engine for the 2D solar system simulation. The simulation provides a
to scale representation of our solar system. The solar distance, planetary
masses/sizes are scaled down by a constant factor. The simulation time is
sped up by a constant factor.

Planet Order (from sun)
1. Mercury
2. Venus
3. Earth
4. Mars
5. Jupiter
6. Saturn
7. Uranus
8. Neptune
*/

#pragma once

#include "Constants.h"
#include "Planet.h"

#include <SDL2/SDL.h>
#include <tuple>
#include <vector>

class SolarSystemEngine {
public:
	SolarSystemEngine();

	/**
	* @brief Initialize the simulation engine.
	* 
	* @returns True if initialized; False otherwise
	*/
	bool initialize();

	/**
	* @brief Run the simulation loop.
	* @note This terminates with the ESC key.
	*/
	void runSimulation();

	/**
	* @brief Shutdown the simulation.
	*/
	void shutdown();

private:
	/**
	* @brief Handle simulation inputs.
	* 
	* ESC - Simulation shutdown
	* Mouse Scroll - Zoom in/out
	* Mouse Click-Drag - Simulation pan
	* Mouse Single Click - Highlight planet
	* Mouse Double Click - Planet details
	*/
	void processInput();

	/**
	* @brief Update the simulation state by moving the planets.
	*/
	void updateSimulation();

	/**
	* @brief Generate the simulation output.
	* @note This draws the simulation to screen.
	*/
	void generateOutput();

	/**
	* @brief Compute the acceleration of a planet.
	*
	* @param[in] x x-coordinate of planet
	* @param[in] y y-coordinate of planet
	* @param[in] sun_mass mass of the sun (central body)
	* @returns acceleration of the planet
	*/
	double computeAcceleration(double x, double y, double sun_mass);

	/**
	* @brief Draw the planet's orbital trace points.
	*/
	void drawTrace();

	/**
	* @brief Draw a planet in the simulation.
	*
	* @param[in] p1 first coordinate of planet
	* @param[in] p2 second coordinate of planet
	* @param[in] r  planet radius
	*/
	void drawPlanet(double x, double y, double r);

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	uint32_t m_ticks_count;
	bool m_running;

	// Simulation Object Data Structures
	std::vector<Planet*> m_planets;

	// Simulation Loop Setings
	const uint8_t FRAME_LIMIT = 16;
	const float MAX_DELTA_TIME = 0.05f;

	// Window Settings
	const char* WINDOW_TITLE = "Solar System 2D Simulation";
	int window_width = 2000;
	int window_height = 2000;
	int prev_window_width;
	int prev_window_height;

	const uint8_t WINDOW_BACKGROUND_RED = 0;
	const uint8_t WINDOW_BACKGROUND_GREEN = 0;
	const uint8_t WINDOW_BACKGROUND_BLUE = 0;
	const uint8_t ORBIT_TRACE_RED = 100;
	const uint8_t ORBIT_TRACE_GREEN = 100;
	const uint8_t ORBIT_TRACE_BLUE = 100;
};