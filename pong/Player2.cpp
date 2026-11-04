/*
Player2.cpp

Description
-----------
Functions declarations for the computer controlled player 2 class.
*/

#include "Player2.h"

Player2::Player2() {}

int Player2::update_paddle_direction(
	float paddle_y, 
	float ball_y,
	float paddle_height,
	int ball_height
) {
	// If ball ABOVE paddle, move paddle up
	if (ball_y < paddle_y) {
		return -1;
	}

	// If ball BELOW paddle, move paddle down
	if (ball_y > paddle_y) {
		return 1;
	}

	// Ball in paddle range, do not move paddle
	return 0;
}