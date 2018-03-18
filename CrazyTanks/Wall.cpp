#include "Wall.h"

Wall::Wall()
{
}



Wall::Wall(int positionX, int positionY, int size, bool isVertical)
{
	positionX_ = positionX;
	positionY_ = positionY;
	size_ = size;
	isVertical_ = isVertical;
}



Wall::~Wall()
{
}



multimap<int, int> Wall::getPositionsXY()
{
	positionsXY_.clear();

	if (isVertical_ == true) {
		for (int y = 0; y < size_; y++)
			positionsXY_.insert(make_pair(positionX_, positionY_ + y));
	}
	else {
		for (int x = 0; x < size_; x++)
			positionsXY_.insert(make_pair(positionX_ + x, positionY_));
	}

	return positionsXY_;
}
