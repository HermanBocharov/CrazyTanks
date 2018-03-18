#include <conio.h>
#include <ctime>
#include <algorithm>

#include "Game.h"
#include "PerformanceCounter.h"

Game::Game()
{
	field_ = new Field();
	playerTank_ = new Player();
}



Game::~Game()
{
}



void Game::pressKey(int keyCode)
{
	eraseObject(*playerTank_);

	if (keyCode == UP_ARROW) {
		if (isRotationObstacles(*playerTank_, Tank::DIRECTION_UP) == false) {
			if (playerTank_->isTurnedUp() == false) {
				if (isMovementObstacles(*playerTank_, Tank::DIRECTION_UP) == false)
					playerTank_->moveUp();
			}
		}
	}
	else if (keyCode == DOWN_ARROW) {
		if (isRotationObstacles(*playerTank_, Tank::DIRECTION_DOWN) == false) {
			if (playerTank_->isTurnedDown() == false) {
				if (isMovementObstacles(*playerTank_, Tank::DIRECTION_DOWN) == false)
					playerTank_->moveDown();
			}
		}
	}
	else if (keyCode == LEFT_ARROW) {
		if (isRotationObstacles(*playerTank_, Tank::DIRECTION_LEFT) == false) {
			if (playerTank_->isTurnedLeft() == false) {
				if (isMovementObstacles(*playerTank_, Tank::DIRECTION_LEFT) == false)
					playerTank_->moveLeft();
			}
		}
	}
	else if (keyCode == RIGHT_ARROW) {
		if (isRotationObstacles(*playerTank_, Tank::DIRECTION_RIGHT) == false) {
			if (playerTank_->isTurnedRight() == false) {
				if (isMovementObstacles(*playerTank_, Tank::DIRECTION_RIGHT) == false)
					playerTank_->moveRight();
			}
		}
	}
	else if (keyCode == SPACE) {
		if (isMovementObstacles(*playerTank_, playerTank_->getCurrentDirection()) == false) { // fix conditions
			isProjectile_ = true;
			playerTank_->fire();
		}
	}
}



void Game::updateFrame()
{
	drawProjectile(playerTank_);
	drawObject(*playerTank_);

	for (int i = 0; i < enemies_.size(); ++i)
		drawProjectile(enemies_[i]);
}



void Game::run()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { 0, 0 };

	Counter timer;
	srand(time(0));
	timer.start();

	Counter deltaTimer;

	drawObject(*playerTank_);
	drawObject(*field_);

	enemyAI_ = getEnemyAI();
	enemyAI_.detach();

	double deltaTime = 0.0;
	while (true) {
		deltaTimer.start();
		
		if (_kbhit())
			pressKey(_getch());

		updateFrame();
		render();

		SetConsoleCursorPosition(hConsole, coord);
		cout << "Time: " << static_cast<int>(timer.getTime() / 1000.0) << " seconds";

		while (true) {
			deltaTime = deltaTimer.getTime();
			if (deltaTime > 50)
				break;
		}
	}
}



bool Game::isMovementObstacles(Tank& tank, int direction)
{
	movementObstaclesXY_ = tank.checkMovementObstacles(direction);

	for (auto it = movementObstaclesXY_.begin(); it != movementObstaclesXY_.end(); ++it) {
		if (getChar( (*it).first, (*it).second ) == DISPLAY_CHAR)
			return true;
	}

	return false;
}



bool Game::isRotationObstacles(Tank& tank, int direction)
{
	rotationObstaclesXY_ = tank.checkRotationObstacles(tank.getCurrentDirection(), direction);

	for (auto it = rotationObstaclesXY_.begin(); it != rotationObstaclesXY_.end(); ++it) {
		if (getChar((*it).first, (*it).second) == DISPLAY_CHAR)
			return true;
	}

	return false;
}



void Game::drawObject(GameObject& gameObj)
{
 	positionsXY_ = gameObj.getPositionsXY();

	for (auto it = positionsXY_.begin(); it != positionsXY_.end(); ++it)
		setChar( (*it).first, (*it).second, DISPLAY_CHAR);
}



void Game::eraseObject(GameObject& gameObj)
{
 	positionsXY_ = gameObj.getPositionsXY();

	for (auto it = positionsXY_.begin(); it != positionsXY_.end(); ++it)
		setChar((*it).first, (*it).second, ' ');
}



void Game::drawProjectile(Tank* tank)
{
	if (isProjectile_ == true) {
		projectiles_ = tank->getProjectiles();

		for (int i = 0; i < projectiles_->size(); ++i) {
			if ((*projectiles_)[i] != 0) {
				eraseObject((*(*projectiles_)[i]));

				if (getChar((*projectiles_)[i]->getNextPositionX(),
					(*projectiles_)[i]->getNextPositionY()) != DISPLAY_CHAR) {
					(*projectiles_)[i]->move();
					drawObject((*(*projectiles_)[i]));
				}
				else {
					eraseObject((*(*projectiles_)[i]));
					delete (*projectiles_)[i];
					projectiles_->erase(projectiles_->begin() + i);
					if (projectiles_->empty() == true)
						isProjectile_ = false;
				}
			}
		}
	}
}


vector<Enemy*> Game::generateEnemies(int nEnemies)
{
	vector<Enemy*> enemies;

	int randomX = 0;
	int randomY = 0;
	bool canGenerate = false;

	multimap<int, int> filledPositionsXY;

	for (int i = 0; i < nEnemies; ++i) {
		canGenerate = false;
		while (canGenerate == false) {
			randomX = 18 + rand() % 26;
			randomY = 1 + rand() % 18;

			canGenerate = ( canGenerateEnemy(randomX, randomY) ) &&
						  ( !hasMultimapKeyValue(filledPositionsXY, randomX, randomY) );
		}

		for (int x = randomX - 2; x < randomX + 5; ++x) {
			for (int y = randomY - 2; y < randomY + 5; ++y) {
				filledPositionsXY.insert(make_pair(x, y));
			}
		}

		enemyTank_ = new Enemy(randomX, randomY, Tank::DIRECTION_UP);
		enemies.push_back(enemyTank_);
	}

	return enemies;
}



bool Game::canGenerateEnemy(int positionX, int positionY)
{
	for (int x = positionX - 1; x < positionX + 4; ++x) {
		for (int y = positionY - 1; y < positionY + 4; ++y) {
			if (getChar(x, y) == DISPLAY_CHAR)
				return false;
		}
	}

	return true;
}



void Game::moveEnemy(Enemy& enemy)
{
	int direction = 1 + rand() % 4;
	int times = 3 + rand() % 6;

	if (direction == Tank::DIRECTION_UP) {
		if (isRotationObstacles(enemy, Tank::DIRECTION_UP) == false) {
			enemy.isTurnedUp();
				if (isMovementObstacles(enemy, Tank::DIRECTION_UP) == false) {
				enemy.moveUp();
				if (isMovementObstacles(enemy, enemy.getCurrentDirection()) == false) { // fix conditions
					isProjectile_ = true;
					enemy.fire();
				}
			}
		}
	}
	else if (direction == Tank::DIRECTION_DOWN) {
		if (isRotationObstacles(enemy, Tank::DIRECTION_DOWN) == false) {
			enemy.isTurnedDown();
			if (isMovementObstacles(enemy, Tank::DIRECTION_DOWN) == false) {
				enemy.moveDown();
			}
		}
	}
	else if (direction == Tank::DIRECTION_LEFT) {
		if (isRotationObstacles(enemy, Tank::DIRECTION_LEFT) == false) {
			enemy.isTurnedLeft();
			if (isMovementObstacles(enemy, Tank::DIRECTION_LEFT) == false) {
				enemy.moveLeft();
			}
		}
	}
	else if (direction == Tank::DIRECTION_RIGHT) {
		if (isRotationObstacles(enemy, Tank::DIRECTION_RIGHT) == false) {
			enemy.isTurnedRight();
			if (isMovementObstacles(enemy, Tank::DIRECTION_RIGHT) == false) {
				enemy.moveRight();
			}
		}
	}
}



void Game::enemyAI()
{
	Counter timer;
	double deltaTime = 0.0;

	enemies_ = generateEnemies(5);

	while (true) {
		timer.start();

		for (int i = 0; i < enemies_.size(); ++i) {
			eraseObject(*enemies_[i]);
			moveEnemy(*enemies_[i]);
			drawObject(*enemies_[i]);
		}
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}



thread Game::getEnemyAI()
{
	return thread([=] { enemyAI(); });
}



bool Game::hasMultimapKeyValue(multimap<int, int> mMap, int key, int value)
{
	auto range = mMap.equal_range(key);
	auto pair = find_if(range.first, range.second,
						[=](auto& el) { return el.second == value; });

	if (pair != range.second)
		return true;
	else
		return false;
}