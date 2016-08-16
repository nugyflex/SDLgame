#include "EnemyDrone.h"
#include <math.h>

EnemyDrone::EnemyDrone() {}

EnemyDrone::EnemyDrone(float x, float y, GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
}

EnemyDrone::~EnemyDrone()
{
}
void EnemyDrone::draw()
{
	spriteSheet.run();
	spriteSheet.draw(boundingBox.x, boundingBox.y);
	firing = false;
	shootCooldown--;
}

void EnemyDrone::calcNewPos(float _x, float _y)
{
	boundingBox.x += boundingBox.w / 2;
	boundingBox.y += boundingBox.h / 2;
	boundingBox.x -= boundingBox.w / 2;
	boundingBox.y -= boundingBox.h / 2;
}

void EnemyDrone::load()
{
	spriteSheet.init(sb, 9, 19, 2, 4, 9, 0, 0);
	spriteSheet.loadTexture("Textures/enemyDrone1.png");
	maxShootCooldown = 20;
}
void EnemyDrone::subtractHealth(int _amount)
{
	health -= _amount;
}
int EnemyDrone::getHealth()
{
	return health;
}
void EnemyDrone::setMode(behaviorType _mode)
{
	mode = _mode;
}
bool EnemyDrone::getFiring()
{
	return firing;
}
glm::vec3 EnemyDrone::getLaserColour()
{
	return laserColour;
}
behaviorType EnemyDrone::getBehaviorType()
{
	return mode;
}