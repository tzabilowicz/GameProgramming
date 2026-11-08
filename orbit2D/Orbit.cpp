/*
Orbit.cpp

Description
-----------
Function definitions for the 2D orbit simulator.
*/

#include "Orbit.h"

#include <cmath>
#include <iostream>

Orbit2D::Orbit2D() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_running(false),
	m_trace_orbit(true)
{}

bool Orbit2D::initialize() {
	// Initialize the SDL library with video subsystem
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);

	if (sdl_result != 0) {
		SDL_Log("Unable to initiaze SDL: %s", SDL_GetError());
		return false;
	}

	// Create the window
	m_window = SDL_CreateWindow(
		WINDOW_TITLE,
		20,  // window x coordinate
		20,  // window y coordinate
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);

	if (!m_window) {
		SDL_Log("Failed to create the SDL window: %s", SDL_GetError());
		return false;
	}

	// Create the graphics renderer
	m_renderer = SDL_CreateRenderer(
		m_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!m_renderer) {
		SDL_Log("Falied to create the SDL renderer: %s", SDL_GetError());
		return false;
	}

	// Create planets
	m_large_planet.x = 0;
	m_large_planet.y = 0;
	m_large_planet.vx = 0;
	m_large_planet.vy = 0;
	m_large_planet.ax = 0;
	m_large_planet.ay = 0;
	m_large_planet.m = EARTH_MASS_KG;
	m_large_planet.r = EARTH_RADIUS_KM;

	m_small_planet.x = DISTANCE_KM;
	m_small_planet.y = 0;
	m_small_planet.vx = 0;
	m_small_planet.vy = std::sqrt(G * EARTH_MASS_KG / DISTANCE_KM);
	m_small_planet.ax = 0;
	m_small_planet.ay = 0;
	m_small_planet.m = MOON_MASS_KG;
	m_small_planet.r = MOON_RADIUS_KM;

	m_running = true;
	return true;
}

void Orbit2D::processInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// Window exit
			case SDL_QUIT:
				m_running = false;
				break;
		}
	}

	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

	// ESC - end game
	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		m_running = false;
	}
}

double Orbit2D::computeAcceleration(double p1, double p2, double central_mass) {
	double mu = G * central_mass;
	double r2 = p1 * p1 + p2 * p2;
	return -mu * p1 / (r2 * std::sqrt(r2));
}

void Orbit2D::updateSimulation() {
	// frame limiting
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + FRAME_LIMIT));

	double delta_t = (SDL_GetTicks() - m_ticks_count) / 1000.0f;

	// clamp to max delta time
	if (delta_t > MAX_DELTA_TIME) {
		delta_t = MAX_DELTA_TIME;
	}

	delta_t *= TIME_SCALE;

	m_ticks_count = SDL_GetTicks();

	// Compute current acceleration
	double curr_ax = computeAcceleration(m_small_planet.x, m_small_planet.y, m_large_planet.m);
	double curr_ay = computeAcceleration(m_small_planet.y, m_small_planet.x, m_large_planet.m);

	// Update planet position
	m_small_planet.x = (
		m_small_planet.x + 
		m_small_planet.vx * delta_t +
		0.5 * m_small_planet.ax * std::pow(delta_t, 2)
	);
	m_small_planet.y = (
		m_small_planet.y + 
		m_small_planet.vy * delta_t + 
		0.5 * m_small_planet.ay * std::pow(delta_t, 2)
	);

	// Compute new accelerations
	m_small_planet.ax = computeAcceleration(m_small_planet.x, m_small_planet.y, m_large_planet.m);
	m_small_planet.ay = computeAcceleration(m_small_planet.y, m_small_planet.x, m_large_planet.m);

	// Compute new velocities
	m_small_planet.vx = m_small_planet.vx + 0.5 * (curr_ax + m_small_planet.ax) * delta_t;
	m_small_planet.vy = m_small_planet.vy + 0.5 * (curr_ay + m_small_planet.ay) * delta_t;
}

void Orbit2D::drawPlanet(double x, double y, double r) {
	for (int w = 0; w < r * 2; w++) {
		for (int h = 0; h < r * 2; h++) {
			double dx = r - w; // horizontal offset
			double dy = r - h; // vertical offset

			if ((dx * dx + dy * dy) <= (r * r)) {
				int x_dx = static_cast<int>(x + dx);
				int y_dy = static_cast<int>(y + dy);

				SDL_RenderDrawPoint(m_renderer, x_dx, y_dy);
			}
		}
	}
}

void Orbit2D::orbitTrace(double x, double y) {
	if (m_orbit_points.size() <= MAX_TRACE_POINTS) {
		m_orbit_points.push_back({ x, y });
	}
	else {
		m_orbit_points.erase(m_orbit_points.begin());
		m_orbit_points.push_back({ x, y });
	}

	for (int i = 0; i < m_orbit_points.size(); i++) {
		SDL_RenderDrawPoint(
			m_renderer,
			static_cast<int>(m_orbit_points[i].x),
			static_cast<int>(m_orbit_points[i].y)
		);
	}
}

void Orbit2D::generateOutput() {
	// Draw background color
	SDL_SetRenderDrawColor(
		m_renderer,
		WINDOW_BACKGROUND_RED,
		WINDOW_BACKGROUND_GREEN,
		WINDOW_BACKGROUND_BLUE,
		255
	);

	// Clear the back buffer
	SDL_RenderClear(m_renderer);

	// Large planet (static)
	SDL_SetRenderDrawColor(
		m_renderer,
		LARGE_PLANET_RED,
		LARGE_PLANET_GREEN,
		LARGE_PLANET_BLUE,
		255
	);

	drawPlanet(
		m_large_planet.x + WINDOW_WIDTH / 2,
		m_large_planet.y + WINDOW_HEIGHT / 2, 
		m_large_planet.r / RADIUS_CONVERSION
	);

	// Small planet (orbiting)
	SDL_SetRenderDrawColor(
		m_renderer,
		SMALL_PLANET_RED,
		SMALL_PLANET_GREEN,
		SMALL_PLANET_BLUE,
		255
	);

	drawPlanet(
		m_small_planet.x / KM_PER_PIXEL + WINDOW_WIDTH / 2,
		m_small_planet.y / KM_PER_PIXEL + WINDOW_HEIGHT / 2,
		m_small_planet.r / RADIUS_CONVERSION
	);

	if (m_trace_orbit) {
		SDL_SetRenderDrawColor(
			m_renderer,
			ORBIT_TRACE_RED,
			ORBIT_TRACE_GREEN,
			ORBIT_TRACE_BLUE,
			255
		);

		orbitTrace(
			m_small_planet.x / KM_PER_PIXEL + WINDOW_WIDTH / 2,
			m_small_planet.y / KM_PER_PIXEL + WINDOW_HEIGHT / 2
		);
	}

	// Swap front and back buffers
	SDL_RenderPresent(m_renderer);
}

void Orbit2D::runSimulationLoop() {
	while (m_running) {
		processInput();
		updateSimulation();
		generateOutput();
	}
}

void Orbit2D::shutdown() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}