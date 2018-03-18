#pragma once

#include <vector>
#include <cstring>

#include "GameObject.h"
#include "Projectile.h"

class Tank : public GameObject
{
public:
	Tank();
	virtual ~Tank();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	virtual bool isTurnedUp() = 0;
	virtual bool isTurnedDown() = 0;
	virtual bool isTurnedLeft() = 0;
	virtual bool isTurnedRight() = 0;

	int getCurrentDirection();

	void fire();
	vector<Projectile*>* getProjectiles();

	virtual multimap<int, int> checkMovementObstacles(int direction);
	virtual multimap<int, int> checkRotationObstacles(int currentDirection, int direction);

	virtual multimap<int, int> getPositionsXY() = 0;

protected:
	int currentDirection_;
	multimap<int, int> movementObstaclesXY_;	
	multimap<int, int> rotationObstaclesXY_;

	Projectile* projectile_;
	vector<Projectile*> projectiles_;
};

