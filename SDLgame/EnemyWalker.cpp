#include "EnemyWalker.h"

EnemyWalker::EnemyWalker(float _x, float _y, GameEngine::SpriteBatch* _sb, ProjectileCollection* _pc){
	sb = _sb;
	pc = _pc;
	vel = 2.5;
	boundingBox.w = 23;
	boundingBox.h = 23;
	boundingBox.x = _x;
	boundingBox.y = _y;
	lightOffSet.x = 0;
	lightOffSet.y = 0;
	health = 1;
	gravity = 0.2;
}
EnemyWalker::~EnemyWalker(){}
void EnemyWalker::run() {
	ai();
	calcNewPos();
}
void EnemyWalker::subtractHealth(float _damage)
{
	health -= _damage;
}
glm::vec2 EnemyWalker::getPosition()
{
	return glm::vec2(boundingBox.x, boundingBox.y);
}
BoundingBox* EnemyWalker::getBoundingBox()
{
	return &boundingBox;
}
int EnemyWalker::getLightID()
{
	return lightID;
}
void EnemyWalker::ai() {
	boundingBox.xv = 0;
	if (boundingBox.onGround) {
		if (!boundingBox.fullyOnGround) {
			if (boundingBox.halfSideLeft) {
				boundingBox.xv = vel;
			}
			else {
				boundingBox.xv = -vel;
			}
		}
		else
		{
			if (target.x < boundingBox.x) {
				boundingBox.xv = -vel;
			}
			else {
				boundingBox.xv = vel;
			}
		}
	}
	boundingBox.onGround = false;
	boundingBox.fullyOnGround = false;
}
void EnemyWalker::calcNewPos() {
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	boundingBox.yv -= gravity;
}

void EnemyWalker::setTarget(float _x, float _y)
{
	target.x = _x;
	target.y = _y;
}

void EnemyWalker::setTarget(glm::vec2 _target)
{
	target = _target;
}

void EnemyWalker::setPosition(float _x, float _y)
{
	boundingBox.x = _x;
	boundingBox.y = _y;
}

float EnemyWalker::getHealth()
{
	return health;
}

void EnemyWalker::load()
{
}

void EnemyWalker::draw()
{
	GameEngine::Color color;
	color.r = 0;
	color.g = 0;
	color.b = 255;
	color.a = 255;
	GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
}

behaviorType EnemyWalker::getMode()
{
	return mode;
}

GameEngine::Light EnemyWalker::getLight()
{
	return Light;
}

glm::vec2 EnemyWalker::getLightOffSet()
{
	return lightOffSet;
}
