/**
SolarSystem.cpp

Description
-----------
Function definitions for the solar system simulation engine.
*/

#include "SolarSystem.h"

#include <cmath>

SolarSystemEngine::SolarSystemEngine() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_ticks_count(0),
	m_running(false)
{
	// Initialize the planet attributes (in order)
	m_planet_attributes.push_back({
		solar_constants::SUN_MASS_KG,
		solar_constants::SUN_RADIUS_KM,
		solar_constants::SUN_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::MERCURY_MASS_KG,
		solar_constants::MERCURY_RADIUS_KM,
		solar_constants::MERCURY_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::VENUS_MASS_KG,
		solar_constants::VENUS_RADIUS_KM,
		solar_constants::VENUS_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::EARTH_MASS_KG,
		solar_constants::EARTH_RADIUS_KM,
		solar_constants::EARTH_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::MARS_MASS_KG,
		solar_constants::MARS_RADIUS_KM,
		solar_constants::MARS_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::JUPITER_MASS_KG,
		solar_constants::JUPITER_RADIUS_KM,
		solar_constants::JUPITER_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::SATURN_MASS_KG,
		solar_constants::SATURN_RADIUS_KM,
		solar_constants::SATURN_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::URANUS_MASS_KG,
		solar_constants::URANUS_RADIUS_KM,
		solar_constants::URANUS_DISTANCE_KM
	});

	m_planet_attributes.push_back({
		solar_constants::NEPTUNE_MASS_KG,
		solar_constants::NEPTUNE_RADIUS_KM,
		solar_constants::NEPTUNE_DISTANCE_KM
	});

	// Initialize the planet colors (in order)
	m_planet_colors.push_back({
		solar_constants::SUN_R,
		solar_constants::SUN_G,
		solar_constants::SUN_B
	});

	m_planet_colors.push_back({
		solar_constants::MERCURY_R,
		solar_constants::MERCURY_G,
		solar_constants::MERCURY_B
	});

	m_planet_colors.push_back({
		solar_constants::VENUS_R,
		solar_constants::VENUS_G,
		solar_constants::VENUS_B
	});

	m_planet_colors.push_back({
		solar_constants::EARTH_R,
		solar_constants::EARTH_G,
		solar_constants::EARTH_B
	});

	m_planet_colors.push_back({
		solar_constants::MARS_R,
		solar_constants::MARS_G,
		solar_constants::MARS_B
	});

	m_planet_colors.push_back({
		solar_constants::JUPITER_R,
		solar_constants::JUPITER_G,
		solar_constants::JUPITER_B
	});

	m_planet_colors.push_back({
		solar_constants::SATURN_R,
		solar_constants::SATURN_G,
		solar_constants::SATURN_B
	});

	m_planet_colors.push_back({
		solar_constants::URANUS_R,
		solar_constants::URANUS_G,
		solar_constants::URANUS_B
	});

	m_planet_colors.push_back({
		solar_constants::NEPTUNE_R,
		solar_constants::NEPTUNE_G,
		solar_constants::NEPTUNE_B
	});
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

	// Create the planet simulation objects
	for (const auto& [mass_kg, radius_km, distance_km] : m_planet_attributes) {
		double velocity_y = 0;
		if (distance_km != 0) {
			velocity_y = std::sqrt(solar_constants::G * solar_constants::SUN_MASS_KG / distance_km);
		}

		Planet planet {
			static_cast<double>(distance_km), 0, // x, y-coordinate
			0, velocity_y,                       // x, y position velocity
			0, 0,                                // x, y position acceleration
			mass_kg,                             // mass
			static_cast<double>(radius_km)       // radius
		};

		m_planets.push_back(planet);
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
		}
	}

	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);

	// ESC - end game
	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		m_running = false;
	}

	// Maintain the screen size
	SDL_GetWindowSize(m_window, &window_width, &window_height);
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
		// Compute current acceleration
		double curr_ax = computeAcceleration(m_planets[i].x, m_planets[i].y, solar_constants::SUN_MASS_KG);
		double curr_ay = computeAcceleration(m_planets[i].y, m_planets[i].x, solar_constants::SUN_MASS_KG);

		// Update planet position
		m_planets[i].x = (
			m_planets[i].x +
			m_planets[i].vx * delta_t +
			0.5 * m_planets[i].ax * std::pow(delta_t, 2)
			);
		m_planets[i].y = (
			m_planets[i].y +
			m_planets[i].vy * delta_t +
			0.5 * m_planets[i].ay * std::pow(delta_t, 2)
			);

		// Compute new accelerations
		m_planets[i].ax = computeAcceleration(m_planets[i].x, m_planets[i].y, solar_constants::SUN_MASS_KG);
		m_planets[i].ay = computeAcceleration(m_planets[i].y, m_planets[i].x, solar_constants::SUN_MASS_KG);

		// Compute new velocities
		m_planets[i].vx = m_planets[i].vx + 0.5 * (curr_ax + m_planets[i].ax) * delta_t;
		m_planets[i].vy = m_planets[i].vy + 0.5 * (curr_ay + m_planets[i].ay) * delta_t;
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
	for (int i = 0; i < m_planet_colors.size(); i++) {
		//! @note the sun scale is smaller than the planet scale
		uint32_t r_divisor = solar_constants::PLANET_CONVERSION;
		if (i == 0) {
			r_divisor = solar_constants::SUN_CONVERSION;
		}

		// Set planet color
		SDL_SetRenderDrawColor(
			m_renderer,
			std::get<0>(m_planet_colors[i]),
			std::get<1>(m_planet_colors[i]),
			std::get<2>(m_planet_colors[i]),
			255
		);

		drawPlanet(
			m_planets[i].x / solar_constants::KM_PER_PIXEL + window_width / 2,
			m_planets[i].y / solar_constants::KM_PER_PIXEL + window_height / 2,
			m_planets[i].r / r_divisor
		);

		// Draw the planet orbital trace
	}

	// Swap front and back buffers
	SDL_RenderPresent(m_renderer);
}