#pragma once

#include <map>

using namespace std;

class GameObject
{
public:
	enum Direction {
		DIRECTION_UP = 1, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
	};

	GameObject();
	virtual ~GameObject();

	void setPositionX(int x);
	void setPositionY(int y);

	int getPositionX();
	int getPositionY();

	virtual multimap<int, int> getPositionsXY() = 0;

protected:
	int positionX_;
	int positionY_;
	multimap<int, int> positionsXY_;
};