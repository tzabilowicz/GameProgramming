/*
Game.cpp

Description
-----------
Functions declarations for the game class.

Reference
---------
Chapter 1: Game Loop and Game Class
Game Programming in C++ - Sanjav Madhav
*/

#include "Game.h"

#include <algorithm>
#include <random>

Game::Game() :
	m_window(nullptr),
	m_renderer(nullptr),
	m_running(false),
	m_ticks_count(0),
	m_player1_paddle_pos{ 0, 0 },
	m_player2_paddle_pos{ 0, 0 },
	m_paddle1_dir(0),
	m_paddle2_dir(0),
	m_player1_score(0),
	m_player2_score(0),
	m_ball_positions{},
	m_ball_velocities{}
{
	m_player2 = Player2();
}

bool Game::initialize() {
	// Initialize the SDL library with the video subsystem
	int sdl_result = SDL_Init(SDL_INIT_VIDEO);

	if (sdl_result != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create the SDL window
	m_window = SDL_CreateWindow(
		WINDOW_TITLE,
		WINDOW_X_COORDINATE,
		WINDOW_Y_COORDINATE,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0 // SDL window flags
	);

	if (!m_window) {
		SDL_Log("Failed to create the SDL window: %s", SDL_GetError());
		return false;
	}
		
	// Create the SDL graphics renderer
	//! @note SDL_RENDERER_ACCELERATED - takes advantage of graphics hardware
	//! @note SDL_RENDERER_PRESENTVSYNC - enable vertical syncronization
	m_renderer = SDL_CreateRenderer(
		m_window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!m_renderer) {
		SDL_Log("Failed to create the SDL renderer: %s", SDL_GetError());
		return false;
	}

	// Initialize paddle positions
	m_player1_paddle_pos.x = 10.0f;
	m_player1_paddle_pos.y = WINDOW_HEIGHT / 2.0f;
	m_player2_paddle_pos.x = WINDOW_WIDTH - 10.0f;
	m_player2_paddle_pos.y = WINDOW_HEIGHT / 2.0f;
	
	// Add the initial ball
	add_ball();

	m_running = true;

	return true;
}

void Game::add_ball() {
	// Initialize ball position
	Vector2 t_ball_pos{
		WINDOW_WIDTH / 2.0f,
		WINDOW_HEIGHT / 2.0f
	};

	m_ball_positions.push_back(t_ball_pos);

	// Initialize ball velocity
	//! @note - velocity is randomized!
	static std::random_device rd;
	static std::default_random_engine e(rd());
	std::uniform_int_distribution<unsigned> u_dir(0, 1);
	std::uniform_int_distribution<unsigned> u_vel(MIN_VELOCITY, MAX_VELOCITY);

	float velocity = static_cast<float>(u_vel(e));

	Vector2 t_ball_vel{ velocity, velocity };

	uint16_t x_direction = u_dir(e);
	uint16_t y_direction = u_dir(e);
	if (x_direction == 0) {
		t_ball_vel.x *= -1;
	}
	if (y_direction == 0) {
		t_ball_vel.y *= -1;
	}

	m_ball_velocities.push_back(t_ball_vel);
}

void Game::remove_balls(std::vector<int> remove_idxs) {
	// Remove in reverse order to avoid shifting issues
	std::sort(remove_idxs.begin(), remove_idxs.end());

	// Remove ball positions and velocities
	for (int i = static_cast<int>(remove_idxs.size()) - 1; i >= 0; i--) {
		int idx = remove_idxs[i];

		// Ensure index is valid before erasing
		if (idx >= 0 && idx < static_cast<int>(m_ball_positions.size())) {
			m_ball_positions.erase(m_ball_positions.begin() + idx);
			m_ball_velocities.erase(m_ball_velocities.begin() + idx);
		}
	}
}

void Game::process_input() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// Handle window exit
		switch (event.type) {
			case SDL_QUIT:
				m_running = false;
				break;
		}
	}
	
	// Get keyboard inputs
	const uint8_t* keyboard_state = SDL_GetKeyboardState(NULL);
	
	// ESC - end game
	if (keyboard_state[SDL_SCANCODE_ESCAPE]) {
		m_running = false;
	}

	m_paddle1_dir = 0;
	m_paddle2_dir = 0;

	// W - player 1 up
	if (keyboard_state[SDL_SCANCODE_W]) {
		m_paddle1_dir -= 1;
	}

	// S - player 1 down
	if (keyboard_state[SDL_SCANCODE_S]) {
		m_paddle1_dir += 1;
	}

	//! @note keyboard-based player 2
	// I - player 2 up
	//if (keyboard_state[SDL_SCANCODE_I]) {
	//	m_paddle2_dir -= 1;
	//}
	
	// K - player 2 down
	//if (keyboard_state[SDL_SCANCODE_K]) {
	//	m_paddle2_dir += 1;
	//}

	//! @note computer-based player 2
	//! @note the computer only plays when there is 1 ball!
	// player 2 direction
	if (m_ball_positions.size() == 1) {
		m_paddle2_dir = m_player2.update_paddle_direction(
			m_player2_paddle_pos.y,
			m_ball_positions[0].y,
			PADDLE_HEIGHT,
			BALL_WIDTH
		);
	}

	// SPACE - add new ball to the game
	if (keyboard_state[SDL_SCANCODE_SPACE]) {
		add_ball();
	}
}

void Game::update_game() {
	// frame limiting
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + FRAME_LIMIT_MS));

	// seconds between frames
	//! @note SDL_GetTicks returns the number of milliseconds
	//!       elapsed since SDL_Init
	float delta_time = (SDL_GetTicks() - m_ticks_count) / 1000.0f;

	// clamp to max delta time
	if (delta_time > MAX_DELTA_TIME) {
		delta_time = MAX_DELTA_TIME;
	}

	m_ticks_count = SDL_GetTicks();
	
	// Update paddle 1 position
	if (m_paddle1_dir != 0) {
		m_player1_paddle_pos.y += m_paddle1_dir * PADDLE_SPEED * delta_time;

		// top wall detection
		if (m_player1_paddle_pos.y < (PADDLE_HEIGHT / 2 + WALL_THICKNESS)) {
			m_player1_paddle_pos.y = PADDLE_HEIGHT / 2 + WALL_THICKNESS;
		}
		// bottom wall detection
		else if (
			m_player1_paddle_pos.y > (WINDOW_HEIGHT - PADDLE_HEIGHT / 2 - WALL_THICKNESS)
		) {
			m_player1_paddle_pos.y = WINDOW_HEIGHT - PADDLE_HEIGHT / 2 - WALL_THICKNESS;
		}
	}

	// Update paddle 2 position
	if (m_paddle2_dir != 0) {
		m_player2_paddle_pos.y += m_paddle2_dir * PADDLE_SPEED * delta_time;

		// top wall detection
		if (m_player2_paddle_pos.y < (PADDLE_HEIGHT / 2 + WALL_THICKNESS)) {
			m_player2_paddle_pos.y = PADDLE_HEIGHT / 2 + WALL_THICKNESS;
		}
		// bottom wall detection
		else if (
			m_player2_paddle_pos.y > (WINDOW_HEIGHT - PADDLE_HEIGHT / 2 - WALL_THICKNESS)
		) {
			m_player2_paddle_pos.y = WINDOW_HEIGHT - PADDLE_HEIGHT / 2 - WALL_THICKNESS;
		}
	}

	std::vector<int> scored_balls;
	for (uint32_t i = 0; i < m_ball_positions.size(); i++) {
		// update y velocity (wall detection)
		if (
			m_ball_positions[i].y <= (WALL_THICKNESS + BALL_WIDTH / 2) &&
			m_ball_velocities[i].y < 0
		) {
			m_ball_velocities[i].y *= -1;
		}
		if (
			m_ball_positions[i].y >= (WINDOW_HEIGHT - WALL_THICKNESS - BALL_WIDTH / 2) &&
			m_ball_velocities[i].y > 0
		) {
			m_ball_velocities[i].y *= -1;
		}

		// update x velocity (paddle detection)
		if (
			m_ball_positions[i].x <= (WALL_THICKNESS + PADDLE_WIDTH + BALL_WIDTH / 2) &&
			m_ball_velocities[i].x < 0
		) {
			// Check paddle hit
			if (
				(m_ball_positions[i].y + BALL_WIDTH / 2) >= (m_player1_paddle_pos.y - PADDLE_HEIGHT / 2) &&
				(m_ball_positions[i].y - BALL_WIDTH / 2) <= (m_player1_paddle_pos.y + PADDLE_HEIGHT / 2)
			) {
				m_ball_velocities[i].x *= -1;
			}
			else {
				// PLAYER 2 scores
				m_player2_score += 1;
				scored_balls.push_back(i);
			}
		}
		if (
			m_ball_positions[i].x >= ( // Player 2 paddle
				WINDOW_WIDTH - WALL_THICKNESS - PADDLE_WIDTH - BALL_WIDTH / 2
			) &&
			m_ball_velocities[i].x > 0
		) {
			// check paddle hit
			if (
				(m_ball_positions[i].y + BALL_WIDTH / 2) >= (m_player2_paddle_pos.y - PADDLE_HEIGHT / 2) &&
				(m_ball_positions[i].y - BALL_WIDTH / 2) <= (m_player2_paddle_pos.y + PADDLE_HEIGHT / 2)
			) {
				m_ball_velocities[i].x *= -1;
			}
			else {
				// PLAYER 1 scores
				m_player1_score += 1;
				scored_balls.push_back(i);
			}
		}

		m_ball_positions[i].x += m_ball_velocities[i].x * delta_time;
		m_ball_positions[i].y += m_ball_velocities[i].y * delta_time;
	}

	// Remove scored balls
	remove_balls(scored_balls);
}

void Game::generate_output() {
	// Draw the background color
	SDL_SetRenderDrawColor(
		m_renderer,
		BACKGROUND_RED,
		BACKGROUND_GREEN,
		BACKGROUND_BLUE,
		BACKGROUND_ALPHA
	);

	// Clear back buffer and draw current buffer
	SDL_RenderClear(m_renderer);

	//! @note draw the top and bottom walls
	SDL_SetRenderDrawColor(
		m_renderer,
		BACKGROUND_RED,
		BACKGROUND_GREEN,
		BACKGROUND_BLUE,
		BACKGROUND_ALPHA
	);

	SDL_Rect top_wall{
		0,
		0,
		WINDOW_WIDTH,
		WALL_THICKNESS
	};

	SDL_Rect bottom_wall{
		0,
		WINDOW_HEIGHT - WALL_THICKNESS,
		WINDOW_WIDTH,
		WALL_THICKNESS
	};

	SDL_RenderFillRect(m_renderer, &top_wall);
	SDL_RenderFillRect(m_renderer, &bottom_wall);

	//! @note draw player 1 paddle
	SDL_SetRenderDrawColor(
		m_renderer,
		PLAYER1_PADDLE_RED,
		PLAYER1_PADDLE_GREEN,
		PLAYER1_PADDLE_BLUE,
		PLAYER1_PADDLE_ALPHA
	);

	SDL_Rect p1_paddle{
		static_cast<int>(m_player1_paddle_pos.x - PADDLE_WIDTH / 2),
		static_cast<int>(m_player1_paddle_pos.y - PADDLE_HEIGHT / 2),
		PADDLE_WIDTH,
		static_cast<int>(PADDLE_HEIGHT)
	};

	SDL_RenderFillRect(m_renderer, &p1_paddle);

	//! @note draw player 2 paddle
	SDL_SetRenderDrawColor(
		m_renderer,
		PLAYER2_PADDLE_RED,
		PLAYER2_PADDLE_GREEN,
		PLAYER2_PADDLE_BLUE,
		PLAYER2_PADDLE_ALPHA
	);

	SDL_Rect p2_paddle{
		static_cast<int>(m_player2_paddle_pos.x - PADDLE_WIDTH / 2),
		static_cast<int>(m_player2_paddle_pos.y - PADDLE_HEIGHT / 2),
		PADDLE_WIDTH,
		static_cast<int>(PADDLE_HEIGHT)
	};

	SDL_RenderFillRect(m_renderer, &p2_paddle);

	for (uint32_t i = 0; i < m_ball_positions.size(); i++) {
		//! @note draw ball
		SDL_SetRenderDrawColor(
			m_renderer,
			BALL_RED,
			BALL_GREEN,
			BALL_BLUE,
			BALL_ALPHA
		);

		SDL_Rect ball{
			static_cast<int>(m_ball_positions[i].x - BALL_WIDTH / 2),
			static_cast<int>(m_ball_positions[i].y - BALL_WIDTH / 2),
			BALL_WIDTH,
			BALL_WIDTH
		};

		SDL_RenderFillRect(m_renderer, &ball);
	}

	// Swap front and back buffers
	SDL_RenderPresent(m_renderer);
}

void Game::run_loop() {
	while (m_running) {
		process_input();
		update_game();
		generate_output();
	}
}

void Game::display_score() {
	std::cout << "Player 1 Score: " << m_player1_score << std::endl;
	std::cout << "Player 2 Score: " << m_player2_score << std::endl;
}

void Game::shutdown() {
	// Destroy and close SDL
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}