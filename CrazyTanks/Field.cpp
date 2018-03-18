#include "Field.h"

Field::Field()
{
	positionX_ = 17;
	positionY_ = 0;
}



Field::~Field()
{
}



Wall Field::generateWall()
{
	int randomX = positionX_ + 1 + rand() % 21;
	int randomY = positionY_ + 1 + rand() % 16;
	int randomSize = 3 + rand() % 3;
	int randomPosition = rand() % 2;

	bool isVertical;
	if (randomPosition == 0)
		isVertical = false;
	else
		isVertical = true;

	Wall wall(randomX, randomY, randomSize, isVertical);

	return wall;
}



multimap<int, int> Field::getPositionsXY()
{
	positionsXY_.clear();

	for (int x = 0; x < FIELD_WIDTH; ++x)
		positionsXY_.insert(make_pair(positionX_ + x, positionY_));

	for (int y = 1; y < FIELD_HEIGHT - 1; ++y)
		positionsXY_.insert(make_pair(positionX_, positionY_ + y));

	for (int y = 1; y < FIELD_HEIGHT - 1; ++y)
		positionsXY_.insert(make_pair(positionX_ + FIELD_WIDTH - 1, positionY_ + y));

	for (int x = 0; x < FIELD_WIDTH; ++x) {
		positionsXY_.insert(make_pair(positionX_ + x, positionY_ + FIELD_HEIGHT - 1));
	}


	nWalls_ = 5 + rand() % 6;

	for (int i = 0; i < nWalls_; i++) {
		wall_ = generateWall();
		auto pos = wall_.getPositionsXY();
		positionsXY_.insert(pos.begin(), pos.end());
	}

	return positionsXY_;
}