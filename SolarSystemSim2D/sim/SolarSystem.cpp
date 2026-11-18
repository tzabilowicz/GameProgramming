/**
SolarSystem.cpp

Description
-----------
Function definitions for the solar system simulation engine.
*/

#include "SolarSystem.h"

#include <cmath>
#include <iostream>

SolarSystemEngine::SolarSystemEngine() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_ticks_count(0),
	m_running(false)
{
	// Initialize the planet attributes (in order)
	m_planets.push_back(new Planet(
		solar_constants::SUN,
		solar_constants::SUN_MASS_KG,
		solar_constants::SUN_RADIUS_KM,
		solar_constants::SUN_DISTANCE_KM,
		solar_constants::SUN_TRACE_POINTS,
		solar_constants::SUN_R,
		solar_constants::SUN_G,
		solar_constants::SUN_B
	));

	m_planets.push_back(new Planet(
		solar_constants::MERCURY,
		solar_constants::MERCURY_MASS_KG,
		solar_constants::MERCURY_RADIUS_KM,
		solar_constants::MERCURY_DISTANCE_KM,
		solar_constants::MERCURY_TRACE_POINTS,
		solar_constants::MERCURY_R,
		solar_constants::MERCURY_G,
		solar_constants::MERCURY_B
	));

	m_planets.push_back(new Planet(
		solar_constants::VENUS,
		solar_constants::VENUS_MASS_KG,
		solar_constants::VENUS_RADIUS_KM,
		solar_constants::VENUS_DISTANCE_KM,
		solar_constants::VENUS_TRACE_POINTS,
		solar_constants::VENUS_R,
		solar_constants::VENUS_G,
		solar_constants::VENUS_B
	));

	m_planets.push_back(new Planet(
		solar_constants::EARTH,
		solar_constants::EARTH_MASS_KG,
		solar_constants::EARTH_RADIUS_KM,
		solar_constants::EARTH_DISTANCE_KM,
		solar_constants::EARTH_TRACE_POINTS,
		solar_constants::EARTH_R,
		solar_constants::EARTH_G,
		solar_constants::EARTH_B
	));

	m_planets.push_back(new Planet(
		solar_constants::MARS,
		solar_constants::MARS_MASS_KG,
		solar_constants::MARS_RADIUS_KM,
		solar_constants::MARS_DISTANCE_KM,
		solar_constants::MARS_TRACE_POINTS,
		solar_constants::MARS_R,
		solar_constants::MARS_G,
		solar_constants::MARS_B
	));

	m_planets.push_back(new Planet(
		solar_constants::JUPITER,
		solar_constants::JUPITER_MASS_KG,
		solar_constants::JUPITER_RADIUS_KM,
		solar_constants::JUPITER_DISTANCE_KM,
		solar_constants::JUPITER_TRACE_POINTS,
		solar_constants::JUPITER_R,
		solar_constants::JUPITER_G,
		solar_constants::JUPITER_B
	));

	m_planets.push_back(new Planet(
		solar_constants::SATURN,
		solar_constants::SATURN_MASS_KG,
		solar_constants::SATURN_RADIUS_KM,
		solar_constants::SATURN_DISTANCE_KM,
		solar_constants::SATURN_TRACE_POINTS,
		solar_constants::SATURN_R,
		solar_constants::SATURN_G,
		solar_constants::SATURN_B
	));

	m_planets.push_back(new Planet(
		solar_constants::URANUS,
		solar_constants::URANUS_MASS_KG,
		solar_constants::URANUS_RADIUS_KM,
		solar_constants::URANUS_DISTANCE_KM,
		solar_constants::URANUS_TRACE_POINTS,
		solar_constants::URANUS_R,
		solar_constants::URANUS_G,
		solar_constants::URANUS_B
	));

	m_planets.push_back(new Planet(
		solar_constants::NEPTUNE,
		solar_constants::NEPTUNE_MASS_KG,
		solar_constants::NEPTUNE_RADIUS_KM,
		solar_constants::NEPTUNE_DISTANCE_KM,
		solar_constants::NEPTUNE_TRACE_POINTS,
		solar_constants::NEPTUNE_R,
		solar_constants::NEPTUNE_G,
		solar_constants::NEPTUNE_B
	));

	prev_window_width = window_width;
	prev_window_height = window_height;
	
	// Set the default scaling ratios
	m_distance_scale = solar_constants::KM_PER_PIXEL;
	m_planet_scale = 1.0;
}

bool SolarSystemEngine::initialize() {
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);

	if (sdl_result != 0) {
		SDL_Log("Unable to initialize simulation: %s", SDL_GetError());
		return false;
	}

	// Create simulation window
	m_window = SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_RESIZABLE
	);

	if (!m_window) {
		SDL_Log("Failed to create simulation window: %s", SDL_GetError());
		return false;
	}

	// Create graphics renderer
	m_renderer = SDL_CreateRenderer(
		m_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!m_renderer) {
		SDL_Log("Failed to create simulation renderer: %s", SDL_GetError());
		return false;
	}

	// Initialize planet attributes
	for (int i = 0; i < m_planets.size(); i++) {
		Planet* t_planet = m_planets[i];

		double velocity_y = 0;

		//! @note Only set the velocity of planets; not sun
		if (t_planet->getDistance() != 0) {
			velocity_y = std::sqrt(
				solar_constants::G * solar_constants::SUN_MASS_KG / 
				t_planet->getDistance()
			);
		}

		t_planet->setPosition(static_cast<double>(t_planet->getDistance()), 0);
		t_planet->setVelocity(0, velocity_y);
		t_planet->setAcceleration(0, 0);
	}

	m_running = true;
	return true;
}

void SolarSystemEngine::runSimulation() {
	while (m_running) {
		processInput();
		updateSimulation();
		generateOutput();
	}
}

void SolarSystemEngine::shutdown() {
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void SolarSystemEngine::processInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// Window exit
		case SDL_QUIT:
			m_running = false;
			break;
		// Scroll to zoom
		case SDL_MOUSEWHEEL:
			m_distance_scale += -event.wheel.y * KM_PER_SCROLL;
			m_planet_scale += -event.wheel.y * RADIUS_SCALE_PER_SCROLL;
		}
	}

	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

	// ESC - end game
	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		m_running = false;
	}

	// Maintain the screen size
	SDL_GetWindowSize(m_window, &window_width, &window_height);

	// If window size changes, clear trace points
	if ((window_width != prev_window_width) || (window_height != prev_window_height)) {
		//! @note Sun has no trace points
		for (int i = 1; i < m_planets.size(); i++) {
			Planet* t_planet = m_planets[i];

			t_planet->clearTracePoints();
		}

		prev_window_width = window_width;
		prev_window_height = window_height;
	}
}

double SolarSystemEngine::computeAcceleration(double p1, double p2, double sun_mass) {
	double mu = solar_constants::G * sun_mass;
	double r2 = p1 * p1 + p2 * p2;
	return -mu * p1 / (r2 * std::sqrt(r2));
}

void SolarSystemEngine::updateSimulation() {
	// frame limiting
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + FRAME_LIMIT));

	double delta_t = (SDL_GetTicks() - m_ticks_count) / 1000.0f;

	// clamp to max delta time
	if (delta_t > MAX_DELTA_TIME) {
		delta_t = MAX_DELTA_TIME;
	}

	delta_t *= solar_constants::TIME_MULTIPLIER;

	m_ticks_count = SDL_GetTicks();

	//! @note do not update the sun's attributes
	for (int i = 1; i < m_planets.size(); i++) {
		Planet* t_planet = m_planets[i];
		
		std::tuple<double, double> t_planet_pos = t_planet->getPosition();
		std::tuple<double, double> t_planet_vel = t_planet->getVelocity();
		std::tuple<double, double> t_planet_acl = t_planet->getAcceleration();

		// Unpack planet attributes
		double x  = std::get<0>(t_planet_pos);
		double y  = std::get<1>(t_planet_pos);
		double vx = std::get<0>(t_planet_vel);
		double vy = std::get<1>(t_planet_vel);
		double ax = std::get<0>(t_planet_acl);
		double ay = std::get<1>(t_planet_acl);

		// Compute current acceleration
		double curr_ax = computeAcceleration(x, y, solar_constants::SUN_MASS_KG);
		double curr_ay = computeAcceleration(y, x, solar_constants::SUN_MASS_KG);

		// Update planet position
		double new_x = x + vx * delta_t + 0.5 * ax * std::pow(delta_t, 2);
		double new_y = y + vy * delta_t + 0.5 * ay * std::pow(delta_t, 2);

		// Compute new accelerations
		double new_ax = computeAcceleration(new_x, new_y, solar_constants::SUN_MASS_KG);
		double new_ay = computeAcceleration(new_y, new_x, solar_constants::SUN_MASS_KG);

		// Compute new velocities
		double new_vx = vx + 0.5 * (ax + new_ax) * delta_t;
		double new_vy = vy + 0.5 * (ay + new_ay) * delta_t;

		// Set new planet attributes
		t_planet->setPosition(new_x, new_y);
		t_planet->setVelocity(new_vx, new_vy);
		t_planet->setAcceleration(new_ax, new_ay);

		// Add trace points
		t_planet->addTracePoint({new_x, new_y});
	}
}

void SolarSystemEngine::drawPlanet(double x, double y, double r) {
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

void SolarSystemEngine::drawTrace() {
	for (int p = 0; p < m_planets.size(); p++) {
		Planet* t_planet = m_planets[p];

		std::vector<Vector2> t_trace_points = t_planet->getTracePoints();
		for (int i = 0; i < t_trace_points.size(); i++) {
			int x = static_cast<int>(t_trace_points[i].x / m_distance_scale + window_width / 2);
			int y = static_cast<int>(t_trace_points[i].y / m_distance_scale + window_height / 2);

			SDL_RenderDrawPoint(m_renderer, x, y);
		}
	}
}

void SolarSystemEngine::generateOutput() {
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

	// Draw the planets
	for (int i = 0; i < m_planets.size(); i++) {
		Planet* t_planet = m_planets[i];

		// Draw trace for planets, not sun
		if (i > 0) {
			SDL_SetRenderDrawColor(
				m_renderer,
				ORBIT_TRACE_RED,
				ORBIT_TRACE_GREEN,
				ORBIT_TRACE_BLUE,
				255
			);

			drawTrace();
		}

		//! @note the sun scale is smaller than the planet scale
		uint32_t r_divisor = solar_constants::PLANET_CONVERSION;
		if (i == 0) {
			r_divisor = solar_constants::SUN_CONVERSION;
		}
		r_divisor *= m_planet_scale;

		// Set planet color
		std::tuple<uint8_t, uint8_t, uint8_t> rgb = t_planet->getRGB();

		SDL_SetRenderDrawColor(
			m_renderer,
			std::get<0>(rgb), // R
			std::get<1>(rgb), // G
			std::get<2>(rgb), // B
			255
		);

		// Get planet position
		std::tuple<double, double> position = t_planet->getPosition();

		drawPlanet(
			std::get<0>(position) / m_distance_scale + window_width / 2,
			std::get<1>(position) / m_distance_scale + window_height / 2,
			t_planet->getRadius() / r_divisor
		);
	}

	// Swap front and back buffers
	SDL_RenderPresent(m_renderer);
}