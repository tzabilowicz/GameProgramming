/*
Game.h

Description
-----------
Specifies the game class for the game of pong.

Reference
---------
Chapter 1: Game Loop and Game Class
Game Programming in C++ - Sanjav Madhav
*/

#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	/**
	* @brief Constructor
	*/
	Game();

	/**
	* @brief Initializes the game class.
	* 
	* Initializes SDL using the video subsystem and creates
	* the SDL window.
	* 
	* @return True if game initialized; False otherwise
	*/
	bool initialize();

	/**
	* @brief Runs the game loop until the game is over.
	*/
	void run_loop();

	/**
	* @brief Displays the score of the game in the terminal.
	*/
	void display_score();

	/**
	* @brief Shutdown the game.
	*/
	void shutdown();

private:
	/**
	* @brief Process the game control inputs.
	* 
	* Termination Inputs:
	*	- Window Close
	*	- Escape Key
	*/
	void process_input();

	/**
	* @brief Update the game state.
	*/
	void update_game();

	/**
	* @brief Generate the game outputs.
	*/
	void generate_output();

	/**
	* @brief Reset the state of the game.
	*/
	void reset_game();

	SDL_Window* m_window;     // window created by SDL
	SDL_Renderer* m_renderer; // renderer for drawing graphics
	bool m_running;           // game running flag
	uint32_t m_ticks_count;   // ticks between frames

	// Game objects
	Vector2 m_player1_paddle_pos;
	Vector2 m_player2_paddle_pos;
	Vector2 m_ball_pos;
	Vector2 m_ball_velocity;

	int8_t m_paddle1_dir; // 0 stationary; 1 up; -1 down
	int8_t m_paddle2_dir; // 0 stationary; 1 up; -1 down

	uint16_t m_player1_score;
	uint16_t m_player2_score;
	
	// Window settings
	const char* WINDOW_TITLE = "Pong";
	const uint16_t WINDOW_X_COORDINATE = 100;
	const uint16_t WINDOW_Y_COORDINATE = 100;
	const uint16_t WINDOW_WIDTH = 1024;
	const uint16_t WINDOW_HEIGHT = 768;
	const uint16_t WALL_THICKNESS = 5;

	// Game colors
	const uint8_t BACKGROUND_RED = 60;
	const uint8_t BACKGROUND_GREEN = 60;
	const uint8_t BACKGROUND_BLUE = 100;
	const uint8_t BACKGROUND_ALPHA = 255;

	const uint8_t PLAYER1_PADDLE_RED = 255;
	const uint8_t PLAYER1_PADDLE_GREEN = 255;
	const uint8_t PLAYER1_PADDLE_BLUE = 255;
	const uint8_t PLAYER1_PADDLE_ALPHA = 255;

	const uint8_t PLAYER2_PADDLE_RED = 65;
	const uint8_t PLAYER2_PADDLE_GREEN = 215;
	const uint8_t PLAYER2_PADDLE_BLUE = 150;
	const uint8_t PLAYER2_PADDLE_ALPHA = 255;

	const uint8_t BALL_RED = 255;
	const uint8_t BALL_GREEN = 185;
	const uint8_t BALL_BLUE = 0;
	const uint8_t BALL_ALPHA = 255;

	// Game object values
	const float PADDLE_HEIGHT = 100.0;
	const int PADDLE_WIDTH = 15;
	const int BALL_WIDTH = 10;
	
	const uint16_t MIN_VELOCITY = 100;
	const uint16_t MAX_VELOCITY = 300;

	// Game loop settings
	const uint8_t FRAME_LIMIT_MS = 16;
	const float MAX_DELTA_TIME = 0.05f;
	const float PADDLE_SPEED = 300.0f;
};