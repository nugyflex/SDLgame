#include "EnemyDrone.h"
#include <math.h>

EnemyDrone::EnemyDrone() {}

EnemyDrone::EnemyDrone(float _x, float _y, GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 18;
	boundingBox.h = 18;
}

EnemyDrone::~EnemyDrone()
{
}
void EnemyDrone::draw()
{
	spriteSheet.run();
	spriteSheet.draw(boundingBox.x + spriteSheetOffSet.x, boundingBox.y + spriteSheetOffSet.y);
}

void EnemyDrone::calcNewPos(float _x, float _y)
{
	boundingBox.y -= + hoverY;
	hoverY += hoverVel;
	if (hoverY > 4) {
		hoverVel -= 0.15;
	}
	if (hoverY < -4) {
		hoverVel += 0.15;
	}
	if (_x != NULL && _y != NULL) {
		float theta = atan(-1 * (_y - boundingBox.y) / (_x - boundingBox.x));
		if (_x > boundingBox.x) {
			boundingBox.yv = sin(theta) * -1 * vel;
			boundingBox.xv = cos(theta) * vel;
		}
		else {
			boundingBox.yv = sin(theta) * vel;
			boundingBox.xv = cos(theta) * -1 * vel;
		}
		if (sqrt(pow(boundingBox.x - _x, 2) + pow(boundingBox.y - _y, 2)) < 100) {
			boundingBox.xv *= -1;
			boundingBox.yv *= -1;
			if (sqrt(pow(boundingBox.x - _x, 2) + pow(boundingBox.y - _y, 2)) > 90) {
				boundingBox.xv = 0;
				boundingBox.yv = 0;
			}
		}
		boundingBox.x += boundingBox.xv;
		boundingBox.y += boundingBox.yv + hoverY;
	}
}

void EnemyDrone::load()
{
	spriteSheet.init(sb, 9, 19, 2, 4, 9, 0, 0);
	spriteSheet.loadTexture("Textures/enemyDrone1.png");
	maxShootCooldown = 20;
	health = 10;
	vel = 2.5;
	hoverVel = -0.5;
	spriteSheetOffSet = glm::vec2(0, -20);
}
void EnemyDrone::run()
{
	shootCooldown--;
	calcNewPos(target.x, target.y);
}
void EnemyDrone::setPosition(float _x, float _y)
{
	boundingBox.x = _x;
	boundingBox.y = _y;
}
void EnemyDrone::setTarget(float _x, float _y)
{
	target.x = _x;
	target.y = _y;
}
void EnemyDrone::setTarget(glm::vec2 _target)
{
	target = _target;
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

BoundingBox * EnemyDrone::getBoundingBox()
{
	return &boundingBox;
}

glm::vec2 EnemyDrone::getPosition()
{
	return glm::vec2(boundingBox.x, boundingBox.y);
}