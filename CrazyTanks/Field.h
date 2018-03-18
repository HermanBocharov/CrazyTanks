#pragma once

#include <vector>

#include "GameObject.h"
#include "Wall.h"

class Field : public GameObject
{
public:
	static const int FIELD_HEIGHT = 25;
	static const int FIELD_WIDTH = 30;

	Field();
	~Field();

	Wall generateWall();

	virtual multimap<int, int> getPositionsXY() override;

private:
	Wall wall_;
	int nWalls_;
};