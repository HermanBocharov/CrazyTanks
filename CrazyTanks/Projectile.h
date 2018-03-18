#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(int positionX, int positionY, int currentDirection);
	~Projectile();

	int getNextPositionX();
	int getNextPositionY();

	void setIsPlayerProjectile(bool flag);

	void move();

	virtual multimap<int, int> getPositionsXY() override;

private:
	int nextPositionX_;
	int nextPositionY_;

	int direction_;
	bool isPlayerProjectile_;
};

