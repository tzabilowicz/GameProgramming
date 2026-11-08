/*
Orbit.h

Description
-----------
Class definition for the 2D-orbit simulator. This simulation provides the
tools to create 2D orbital simulations.
*/

#pragma once

#include <SDL2/SDL.h>
#include <vector>

// Constants
const double G = 6.67430e-20;

const double EARTH_MASS_KG = 5.972e24;
const uint16_t EARTH_RADIUS_KM = 6371;
const double MOON_MASS_KG = 7.347e22;
const double MOON_RADIUS_KM = 1737.4;

const int DISTANCE_KM = 384000;
const uint8_t RADIUS_CONVERSION = 100;
const int KM_PER_PIXEL = 1000;

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

class Orbit2D {
public:
	Orbit2D();

	bool initialize();
	void runSimulationLoop();
	void shutdown();

private:
	void processInput();
	void updateSimulation();
	void generateOutput();
	
	/**
	* @brief Compute the acceleration of a planet.
	* 
	* @param[in] x x-coordinate of planet
	* @param[in] y y-coordinate of planet
	* @param[in] central_mass mass of the central body
	* @returns acceleration of the planet
	*/
	double computeAcceleration(double x, double y, double central_mass);

	/**
	* @brief Draw a planet in the simulation.
	* 
	* @param[in] p1 first coordinate of planet
	* @param[in] p2 second coordinate of planet
	* @param[in] r radius for the circle
	*/
	void drawPlanet(double x, double y, double r);
		
	/**
	* @brief Draws line for the orbit trace.
	* 
	* @param[in] x point x-coordinate
	* @param[in] y point y-coordinate
	*/
	void orbitTrace(double x, double y);

	SDL_Window* m_window;     // window created by SDL
	SDL_Renderer* m_renderer; // renderer for drawing graphics
	uint32_t m_ticks_count;   // ticks between the number of frames
	bool m_running;           // running flag
	bool m_trace_orbit;       // orbital trace flag

	// Simulation Objects
	Planet m_small_planet;
	Planet m_large_planet;
	std::vector<Vector2> m_orbit_points;

	// Window Settings
	const char* WINDOW_TITLE = "2D Orbit Simulation";
	const uint16_t WINDOW_WIDTH = 2048;
	const uint16_t WINDOW_HEIGHT = 1024;

	// Simulation Color Settings
	const uint8_t WINDOW_BACKGROUND_RED = 0;
	const uint8_t WINDOW_BACKGROUND_GREEN = 0;
	const uint8_t WINDOW_BACKGROUND_BLUE = 0;

	const uint8_t LARGE_PLANET_RED = 0;
	const uint8_t LARGE_PLANET_GREEN = 0;
	const uint8_t LARGE_PLANET_BLUE = 255;
	const uint8_t SMALL_PLANET_RED = 211;
	const uint8_t SMALL_PLANET_GREEN = 211;
	const uint8_t SMALL_PLANET_BLUE = 211;

	const uint8_t ORBIT_TRACE_RED = 100;
	const uint8_t ORBIT_TRACE_GREEN = 100;
	const uint8_t ORBIT_TRACE_BLUE = 100;

	// Simulation Loop Settings
	const uint8_t FRAME_LIMIT = 16;
	const float MAX_DELTA_TIME = 0.05f;
	const double TIME_SCALE = 100000.0;
	const int MAX_TRACE_POINTS = 700;
};