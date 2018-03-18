#include "Projectile.h"

Projectile::Projectile(int positionX, int positionY, int currentDirection)
{
	positionX_ = positionX;
	positionY_ = positionY;
	direction_ = currentDirection;
	nextPositionX_ = positionX_;
	nextPositionY_ = positionY_;
}



Projectile::~Projectile()
{
}



int Projectile::getNextPositionX()
{
	return nextPositionX_;
}



int Projectile::getNextPositionY()
{
	return nextPositionY_;
}



void Projectile::setIsPlayerProjectile(bool flag)
{
	isPlayerProjectile_ = flag;
}



void Projectile::move()
{
	switch (direction_) {
		case DIRECTION_UP :
			positionY_ = positionY_ - 1;
			nextPositionY_ = positionY_ - 1;
			break;
		case DIRECTION_DOWN :
			positionY_ = positionY_ + 1;
			nextPositionY_ = positionY_ + 1;
			break;
		case DIRECTION_LEFT :
			positionX_ = positionX_ - 1;
			nextPositionX_ = positionX_ - 1;
			break;
		case DIRECTION_RIGHT :
			positionX_ = positionX_ + 1;
			nextPositionX_ = positionX_ + 1;
			break;
	}
}



multimap<int, int> Projectile::getPositionsXY()
{
	positionsXY_.clear();
	positionsXY_.insert(make_pair(positionX_, positionY_));

	return positionsXY_;
}
