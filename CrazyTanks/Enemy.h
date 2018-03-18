#pragma once

#include "Tank.h"

class Enemy : public Tank
{
public:
	Enemy(int positionX, int positionY, int direction);
	~Enemy();

	virtual bool isTurnedUp() override;
	virtual bool isTurnedDown() override;
	virtual bool isTurnedLeft() override;
	virtual bool isTurnedRight() override;

	virtual multimap<int, int> getPositionsXY() override;

private:
	static const int TANK_HEIGHT = 3;
	static const int TANK_WIDTH = 3;

	int enemyTank_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 0 },
		{ 1, 1, 1 },
		{ 1, 0, 1 }
	};

	int enemyDirectionUp_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 0 },
		{ 1, 1, 1 },
		{ 1, 0, 1 }
	};

	int enemyDirectionDown_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 1, 0 }
	};

	int enemyDirectionLeft_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 1 },
		{ 1, 1, 0 },
		{ 0, 1, 1 }
	};

	int enemyDirectionRight_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 1, 1, 0 },
		{ 0, 1, 1 },
		{ 1, 1, 0 }
	};
};