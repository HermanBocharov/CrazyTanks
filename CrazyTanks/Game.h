#pragma once

#include <thread>
#include <chrono>

#include "ConsoleApp.h"
#include "Player.h"
#include "Enemy.h"
#include "Field.h"
#include "Projectile.h"

class Game : public ConsoleApp
{
public:
	const int SPACE = 32;
	const int UP_ARROW = 72;
	const int DOWN_ARROW = 80;
	const int LEFT_ARROW = 75;
	const int RIGHT_ARROW = 77;

	static Game& getInstance()
	{
		static Game instance;
		return instance;
	}

	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	virtual void pressKey(int keyCode) override;
	virtual void updateFrame() override;
	virtual void run() override;

	bool isMovementObstacles(Tank& tank, int direction);
	bool isRotationObstacles(Tank& tank, int direction);

	void drawObject(GameObject& gameObj);
	void eraseObject(GameObject& gameObj);
	void drawProjectile(Tank* tank);

	vector<Enemy*> generateEnemies(int nEnemies);
	bool canGenerateEnemy(int positionX, int positionY);

	void moveEnemy(Enemy& enemy);

	void enemyAI();
	thread getEnemyAI();

	bool hasMultimapKeyValue(multimap<int, int> mMap, int key, int value);

private:
	const char DISPLAY_CHAR = 2;

	Game();
	~Game();

	Field* field_;
	Player* playerTank_;
	Enemy* enemyTank_;
	vector<Enemy*> enemies_;

	vector<Projectile*>* projectiles_;
	bool isProjectile_ = false;

	multimap<int, int> positionsXY_;
	multimap<int, int> movementObstaclesXY_;
	multimap<int, int> rotationObstaclesXY_;

	thread enemyAI_;
};