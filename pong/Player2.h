/*
Player2.h

Description
-----------
Specifies the computer controlled player 2 class.
*/

#pragma once

class Player2 {
public:
	/**
	* @brief Constructor
	*/
	Player2();

	/**
	* @brief Update the direction of the player 2 paddle.
	* The direction is updated using the y-coordinate of the
	* paddle and y-coordinate of ball. The objective is to
	* match the postion of the paddle and ball.
	* @note This only moves the paddle postion up/down 1 unit.
	* 
	* @param[in] paddle_y y-coordinate of paddle location
	* @param[in] ball_y y-coordinate of ball location
	* @param[in] paddle_height height of the paddle
	* @param[in] ball_height height of the ball
	* @returns -1 to move paddle up; 1 to move paddle down
	*/
	int update_paddle_direction(
		float paddle_y, 
		float ball_y,
		float paddle_height,
		int ball_height
	);
};