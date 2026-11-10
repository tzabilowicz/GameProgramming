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

#include <SDL2/SDL.h>
#include <tuple>
#include <vector>

struct Planet {
	double x;  // x-coordinate of planet center
	double y;  // y-coordinate of planet center
	double vx; // x position velocity
	double vy; // y position velocity
	double ax; // x position acceleration
	double ay; // y position acceleration
	double m;  // planet mass (kg)
	double r;  // planet radius (km)
};

struct Vector2 {
	double x;
	double y;
};

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
	* @brief Draw a planet in the simulation.
	*
	* @param[in] p1 first coordinate of planet
	* @param[in] p2 second coordinate of planet
	* @param[in] r  planet radius
	*/
	void drawPlanet(double x, double y, double r);

	/**
	* @brief Draws orbital trace line.
	*
	* @param[in] x point x-coordinate
	* @param[in] y point y-coordinate
	*/
	void orbitalTrace(double x, double y);

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	uint32_t m_ticks_count;
	bool m_running;

	// Simulation Object Data Structures
	std::vector<Planet> m_planets;
	std::vector<std::vector<Vector2>> m_orbital_trace_points;

	std::vector<std::tuple<double, uint32_t, int64_t>> m_planet_attributes;
	std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> m_planet_colors;

	// Simulation Loop Setings
	const uint8_t FRAME_LIMIT = 16;
	const float MAX_DELTA_TIME = 0.05f;
	const uint16_t MAX_TRACE_POINTS = 800;

	// Window Settings
	const char* WINDOW_TITLE = "Solar System 2D Simulation";
	int window_width = 2000;
	int window_height = 2000;

	const uint8_t WINDOW_BACKGROUND_RED = 0;
	const uint8_t WINDOW_BACKGROUND_GREEN = 0;
	const uint8_t WINDOW_BACKGROUND_BLUE = 0;
};