#include "Tank.h"

Tank::Tank()
{
}



Tank::~Tank()
{
}



void Tank::moveUp()
{
	positionY_ = positionY_ - 1;
}



void Tank::moveDown()
{
	positionY_ = positionY_ + 1;
}



void Tank::moveLeft()
{
	positionX_ = positionX_ - 1;
}



void Tank::moveRight()
{
	positionX_ = positionX_ + 1;
}



int Tank::getCurrentDirection()
{
	return currentDirection_;
}



void Tank::fire()
{
	if (currentDirection_ == DIRECTION_UP) {
		projectile_ = new Projectile(positionX_ + 1, positionY_, currentDirection_);
		projectile_->setIsPlayerProjectile(true);
	}
	else if (currentDirection_ == DIRECTION_DOWN) {
		projectile_ = new Projectile(positionX_ + 1, positionY_ + 2, currentDirection_);
		projectile_->setIsPlayerProjectile(true);
	}
	else if (currentDirection_ == DIRECTION_LEFT) {
		projectile_ = new Projectile(positionX_, positionY_ + 1, currentDirection_);
		projectile_->setIsPlayerProjectile(true);
	}
	else if (currentDirection_ == DIRECTION_RIGHT) {
		projectile_ = new Projectile(positionX_ + 2, positionY_ + 1, currentDirection_);
		projectile_->setIsPlayerProjectile(true);
	}

	projectiles_.push_back(projectile_);
}



vector<Projectile*>* Tank::getProjectiles()
{
	return &projectiles_;
}



multimap<int, int> Tank::checkMovementObstacles(int direction)
{
	movementObstaclesXY_.clear();

	switch (direction) {
		case DIRECTION_UP :
			movementObstaclesXY_.insert(make_pair(positionX_, positionY_));
			movementObstaclesXY_.insert(make_pair(positionX_ + 1, positionY_ - 1));
			movementObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_));
			break;

		case DIRECTION_DOWN :
			movementObstaclesXY_.insert(make_pair(positionX_, positionY_ + 2));
			movementObstaclesXY_.insert(make_pair(positionX_ + 1, positionY_ + 3));
			movementObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_ + 2));
			break;

		case DIRECTION_LEFT :
			movementObstaclesXY_.insert(make_pair(positionX_, positionY_));
			movementObstaclesXY_.insert(make_pair(positionX_ - 1, positionY_ + 1));
			movementObstaclesXY_.insert(make_pair(positionX_, positionY_ + 2));
			break;

		case DIRECTION_RIGHT :
			movementObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_));
			movementObstaclesXY_.insert(make_pair(positionX_ + 3, positionY_ + 1));
			movementObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_ + 2));
			break;
	}

	return movementObstaclesXY_;
}



multimap<int, int> Tank::checkRotationObstacles(int currentDirection, int direction)
{
	rotationObstaclesXY_.clear();

	switch (currentDirection) {
		case DIRECTION_UP :
			switch (direction) {
				case DIRECTION_DOWN :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 1, positionY_ + 3));
					break;

				case DIRECTION_LEFT :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_));
					break;

				case DIRECTION_RIGHT :
					rotationObstaclesXY_.insert(make_pair(positionX_, positionY_));
					break;
			}
			break;

		case DIRECTION_DOWN :
			switch (direction) {
				case DIRECTION_UP :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 1, positionY_ - 1));
					break;

				case DIRECTION_LEFT :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_ + 2));
					break;

				case DIRECTION_RIGHT :
					rotationObstaclesXY_.insert(make_pair(positionX_, positionY_ + 2));
					break;
			}
			break;

		case DIRECTION_LEFT :
			switch (direction) {
				case DIRECTION_UP :
					rotationObstaclesXY_.insert(make_pair(positionX_, positionY_ + 2));
					break;

				case DIRECTION_DOWN :
					rotationObstaclesXY_.insert(make_pair(positionX_, positionY_));
					break;

				case DIRECTION_RIGHT :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 3, positionY_ + 1));
					break;
			}
			break;

		case DIRECTION_RIGHT :
			switch (direction) {
				case DIRECTION_UP :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_ + 2));
					break;

				case DIRECTION_DOWN :
					rotationObstaclesXY_.insert(make_pair(positionX_ + 2, positionY_));
					break;

				case DIRECTION_LEFT :
					rotationObstaclesXY_.insert(make_pair(positionX_ - 1, positionY_ + 1));
					break;
			}
			break;
		}

	return rotationObstaclesXY_;
}