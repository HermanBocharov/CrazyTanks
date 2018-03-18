#include "Player.h"

Player::Player()
{
	positionX_ = 30;
	positionY_ = 21;
	currentDirection_ = DIRECTION_UP;
}



Player::~Player()
{
}



bool Player::isTurnedUp()
{
	if (currentDirection_ != DIRECTION_UP) {
		memcpy(playerTank_, playerDirectionUp_, sizeof(playerTank_));

		if (currentDirection_ == DIRECTION_DOWN)
			positionY_ = positionY_ - 1;

		currentDirection_ = DIRECTION_UP;

		return true;
	}

	return false;
}



bool Player::isTurnedDown()
{
	if (currentDirection_ != DIRECTION_DOWN) {
		memcpy(playerTank_, playerDirectionDown_, sizeof(playerTank_));

		if (currentDirection_ == DIRECTION_UP)
			positionY_ = positionY_ + 1;

		currentDirection_ = DIRECTION_DOWN;

		return true;
	}

	return false;
}



bool Player::isTurnedLeft()
{
	if (currentDirection_ != DIRECTION_LEFT) {
		memcpy(playerTank_, playerDirectionLeft_, sizeof(playerTank_));

		if (currentDirection_ == DIRECTION_RIGHT)
			positionX_ = positionX_ - 1;

		currentDirection_ = DIRECTION_LEFT;

		return true;
	}

	return false;
}



bool Player::isTurnedRight()
{
	if (currentDirection_ != DIRECTION_RIGHT) {
		memcpy(playerTank_, playerDirectionRight_, sizeof(playerTank_));

		if (currentDirection_ == DIRECTION_LEFT)
			positionX_ = positionX_ + 1;

		currentDirection_ = DIRECTION_RIGHT;

		return true;
	}

	return false;
}



multimap<int, int> Player::getPositionsXY()
{
	positionsXY_.clear();

	for (int x = 0; x < TANK_WIDTH; ++x) {
		for (int y = 0; y < TANK_HEIGHT; ++y) {
			if (playerTank_[y][x] == 1) {
				positionsXY_.insert(make_pair(positionX_ + x, positionY_ + y));
			}
		}
	}

	return positionsXY_;
}