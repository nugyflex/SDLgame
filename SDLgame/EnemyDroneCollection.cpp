#include "EnemyDroneCollection.h"
EnemyDroneCollection::EnemyDroneCollection() {}
EnemyDroneCollection::~EnemyDroneCollection() {}
void EnemyDroneCollection::init(GameEngine::SpriteBatch* _sb) {
	sb = _sb;
}
void EnemyDroneCollection::add(float _x, float _y) {
	enemyDroneVector.push_back(new EnemyDrone(_x, _y, sb));
	enemyDroneVector[enemyDroneVector.size() - 1]->setPosition(_x, _y);
	enemyDroneVector[enemyDroneVector.size() - 1]->load();
}

void EnemyDroneCollection::addWorldItemCollection(WorldItemCollection* _worldItems)
{
	worldItems = _worldItems;
}

void EnemyDroneCollection::run() {
	for (int i = 0; i < enemyDroneVector.size(); i++)
	{
		enemyDroneVector[i]->setTarget(glm::vec2(targets[getClosestTarget(i)]->x, targets[getClosestTarget(i)]->y));
		enemyDroneVector[i]->run();
		if (enemyDroneVector[i]->getHealth() <= 0) {
			remove(i);
			i--;
		}
	}
}
EnemyDrone* EnemyDroneCollection::getDrone(int _index)
{
	return enemyDroneVector[_index];
}
void EnemyDroneCollection::reduceHealth(int _index, float _health)
{
	enemyDroneVector[_index]->subtractHealth(_health);
	if (enemyDroneVector[_index]->getHealth() <= 0) {
		worldItems->addItem(explosion, enemyDroneVector[_index]->getBoundingBox()->x + enemyDroneVector[_index]->getBoundingBox()->w / 2, enemyDroneVector[_index]->getBoundingBox()->y + enemyDroneVector[_index]->getBoundingBox()->h / 2);
		remove(_index);
	}
}
void EnemyDroneCollection::draw() {
	for (int i = 0; i < enemyDroneVector.size(); i++)
	{
		enemyDroneVector[i]->draw();
	}
}
BoundingBox* EnemyDroneCollection::getBoundingBox(int _index) {
	return enemyDroneVector[_index]->getBoundingBox();
}
void EnemyDroneCollection::remove(int _index) {
	enemyDroneVector.erase(enemyDroneVector.begin() + _index);
}

int EnemyDroneCollection::getClosestTarget(int _index)
{
	float distance = 1000000;
	int index = -1;
	for (int i = 0; i < targets.size(); i++) {
		if (cd.getDistance(glm::vec2(targets[i]->x, targets[i]->y), enemyDroneVector[_index]->getPosition()) < distance) {
			distance = cd.getDistance(glm::vec2(targets[i]->x, targets[i]->y), enemyDroneVector[_index]->getPosition());
			index = i;
		}
	}
	return index;
}

void EnemyDroneCollection::addTarget(BoundingBox* _boundingBox) {
	targets.push_back(_boundingBox);
}