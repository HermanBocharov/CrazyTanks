#pragma once

#include "Tank.h"

class Player : public Tank
{
public:
	Player();
	~Player();

	virtual bool isTurnedUp() override;
	virtual bool isTurnedDown() override;
	virtual bool isTurnedLeft() override;
	virtual bool isTurnedRight() override;

	virtual multimap<int, int> getPositionsXY() override;

private:
	static const int TANK_HEIGHT = 3;
	static const int TANK_WIDTH = 3;

	int playerTank_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 0 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};

	int playerDirectionUp_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 0 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};

	int playerDirectionDown_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 0, 1, 0 }
	};

	int playerDirectionLeft_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 0, 1, 1 },
		{ 1, 1, 1 },
		{ 0, 1, 1 }
	};

	int playerDirectionRight_[TANK_HEIGHT][TANK_WIDTH] = {
		{ 1, 1, 0 },
		{ 1, 1, 1 },
		{ 1, 1, 0 }
	};
};

