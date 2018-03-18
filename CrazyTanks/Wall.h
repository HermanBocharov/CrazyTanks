#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	Wall(int positionX, int positionY, int size, bool isVertical);
	~Wall();

	virtual multimap<int, int> getPositionsXY() override;

private:
	bool isVertical_;
	int size_;
};

