
#include "EnemyWalkerCollection.h"

EnemyWalkerCollection::EnemyWalkerCollection() {}
EnemyWalkerCollection::~EnemyWalkerCollection() {}
void EnemyWalkerCollection::init(GameEngine::SpriteBatch* _sb, WorldItemCollection* _worldItems, GameEngine::Camera2D* _camera, LightCollection* _LC, ProjectileCollection* _pc) {
	sb = _sb;
	worldItems = _worldItems;
	camera = _camera;
	LC = _LC;
	pc = _pc;
}
void EnemyWalkerCollection::add(float _x, float _y) {
	enemyWalkerVector.push_back(new EnemyWalker(_x, _y, sb, pc));
	enemyWalkerVector[enemyWalkerVector.size() - 1]->setPosition(_x, _y);
	enemyWalkerVector[enemyWalkerVector.size() - 1]->load();
	GameEngine::Light tempLight;
	tempLight = enemyWalkerVector[enemyWalkerVector.size() - 1]->getLight();
	enemyWalkerVector[enemyWalkerVector.size() - 1]->setLightID(LC->addLight(tempLight));
}

void EnemyWalkerCollection::run() {
	for (int i = 0; i < enemyWalkerVector.size(); i++)
	{
		enemyWalkerVector[i]->setTarget(glm::vec2(targets[getClosestTarget(i)]->x + targets[getClosestTarget(i)]->w / 2, targets[getClosestTarget(i)]->y + targets[getClosestTarget(i)]->h / 2));
		enemyWalkerVector[i]->run();
		if (enemyWalkerVector[i]->getHealth() <= 0) {
			remove(i);
			i--;
		}
	}
	linkToLights();
}
EnemyWalker* EnemyWalkerCollection::getWalker(int _index)
{
	return enemyWalkerVector[_index];
}
void EnemyWalkerCollection::reduceHealth(int _index, float _health)
{
	enemyWalkerVector[_index]->subtractHealth(_health);
	if (enemyWalkerVector[_index]->getHealth() <= 0) {
		worldItems->addItem(explosion, enemyWalkerVector[_index]->getBoundingBox()->x + enemyWalkerVector[_index]->getBoundingBox()->w / 2, enemyWalkerVector[_index]->getBoundingBox()->y + enemyWalkerVector[_index]->getBoundingBox()->h / 2);
		camera->setScreenShakeIntensity(7.5);
		remove(_index);
	}
}
void EnemyWalkerCollection::linkToLights()
{
	for (int i = 0; i < enemyWalkerVector.size(); i++)
	{
		if (enemyWalkerVector[i]->getLightID() != -1) {
			glm::vec2 temppos = enemyWalkerVector[i]->getLightOffSet() + glm::vec2(enemyWalkerVector[i]->getBoundingBox()->x, enemyWalkerVector[i]->getBoundingBox()->y);
			LC->changePosition(enemyWalkerVector[i]->getLightID(), temppos.x, temppos.y);
		}
	}
}
void EnemyWalkerCollection::draw() {
	for (int i = 0; i < enemyWalkerVector.size(); i++)
	{
		if (enemyWalkerVector[i]->getMode() == active && LC->getRadius(enemyWalkerVector[i]->getLightID()) < 20) {
			LC->addToRadius(enemyWalkerVector[i]->getLightID(), 0.5);
		}
		enemyWalkerVector[i]->draw();
	}
}
BoundingBox* EnemyWalkerCollection::getBoundingBox(int _index) {
	return enemyWalkerVector[_index]->getBoundingBox();
}
void EnemyWalkerCollection::remove(int _index) {
	if (enemyWalkerVector[_index]->getLightID() != -1) {
		LC->removeLight(enemyWalkerVector[_index]->getLightID());
	}
	enemyWalkerVector.erase(enemyWalkerVector.begin() + _index);
}

int EnemyWalkerCollection::getClosestTarget(int _index)
{
	float distance = 1000000;
	int index = -1;
	for (int i = 0; i < targets.size(); i++) {
		if (cd.getDistance(glm::vec2(targets[i]->x + targets[i]->w / 2, targets[i]->y + targets[i]->h / 2), enemyWalkerVector[_index]->getPosition()) < distance) {
			distance = cd.getDistance(glm::vec2(targets[i]->x + targets[i]->w / 2, targets[i]->y + targets[i]->h), enemyWalkerVector[_index]->getPosition());
			index = i;
		}
	}
	return index;
}

void EnemyWalkerCollection::addTarget(BoundingBox* _boundingBox) {
	targets.push_back(_boundingBox);
}