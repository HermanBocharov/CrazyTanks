#include "Enemy.h"

Enemy::Enemy(int positionX, int positionY, int direction)
{
	positionX_ = positionX;
	positionY_ = positionY;
	currentDirection_ = direction;
}



Enemy::~Enemy()
{
}



bool Enemy::isTurnedUp()
{
	if (currentDirection_ != DIRECTION_UP) {
		memcpy(enemyTank_, enemyDirectionUp_, sizeof(enemyTank_));

		if (currentDirection_ == DIRECTION_DOWN)
			positionY_ = positionY_ - 1;

		currentDirection_ = DIRECTION_UP;

		return true;
	}

	return false;
}



bool Enemy::isTurnedDown()
{
	if (currentDirection_ != DIRECTION_DOWN) {
		memcpy(enemyTank_, enemyDirectionDown_, sizeof(enemyTank_));

		if (currentDirection_ == DIRECTION_UP)
			positionY_ = positionY_ + 1;

		currentDirection_ = DIRECTION_DOWN;

		return true;
	}

	return false;
}



bool Enemy::isTurnedLeft()
{
	if (currentDirection_ != DIRECTION_LEFT) {
		memcpy(enemyTank_, enemyDirectionLeft_, sizeof(enemyTank_));

		if (currentDirection_ == DIRECTION_RIGHT)
			positionX_ = positionX_ - 1;

		currentDirection_ = DIRECTION_LEFT;

		return true;
	}

	return false;
}



bool Enemy::isTurnedRight()
{
	if (currentDirection_ != DIRECTION_RIGHT) {
		memcpy(enemyTank_, enemyDirectionRight_, sizeof(enemyTank_));

		if (currentDirection_ == DIRECTION_LEFT)
			positionX_ = positionX_ + 1;

		currentDirection_ = DIRECTION_RIGHT;

		return true;
	}

	return false;
}



multimap<int, int> Enemy::getPositionsXY()
{
	positionsXY_.clear();

	for (int x = 0; x < TANK_WIDTH; ++x) {
		for (int y = 0; y < TANK_HEIGHT; ++y) {
			if (enemyTank_[y][x] == 1) {
				positionsXY_.insert(make_pair(positionX_ + x, positionY_ + y));
			}
		}
	}

	return positionsXY_;
}