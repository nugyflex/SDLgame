
#include "EnemyDroneCollection.h"

EnemyDroneCollection::EnemyDroneCollection() {}
EnemyDroneCollection::~EnemyDroneCollection() {}
void EnemyDroneCollection::init(GameEngine::SpriteBatch* _sb, WorldItemCollection* _worldItems, GameEngine::Camera2D* _camera, LightCollection* _LC, ProjectileCollection* _pc) {
	sb = _sb;
	worldItems = _worldItems;
	camera = _camera;
	LC = _LC;
	pc = _pc;
}
void EnemyDroneCollection::add(float _x, float _y) {
	enemyDroneVector.push_back(new EnemyDrone(_x, _y, sb, pc));
	enemyDroneVector[enemyDroneVector.size() - 1]->setPosition(_x, _y);
	enemyDroneVector[enemyDroneVector.size() - 1]->load();
	GameEngine::Light tempLight;
	tempLight = enemyDroneVector[enemyDroneVector.size() - 1]->getLight();
	enemyDroneVector[enemyDroneVector.size() - 1]->setLightID(LC->addLight(tempLight));
}

void EnemyDroneCollection::run() {
	for (int i = 0; i < enemyDroneVector.size(); i++)
	{
		enemyDroneVector[i]->setTarget(glm::vec2(targets[getClosestTarget(i)]->x + targets[getClosestTarget(i)]->w/2, targets[getClosestTarget(i)]->y + targets[getClosestTarget(i)]->h/2));
		enemyDroneVector[i]->run();
		if (enemyDroneVector[i]->getHealth() <= 0) {
			remove(i);
			i--;
		}
	}
	linkToLights();
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
		camera->setScreenShakeIntensity(5);
		remove(_index);
	}
}
void EnemyDroneCollection::linkToLights()
{
	for (int i = 0; i < enemyDroneVector.size(); i++)
	{
		if (enemyDroneVector[i]->getLightID() != -1) {
			glm::vec2 temppos = enemyDroneVector[i]->getLightOffSet() + glm::vec2(enemyDroneVector[i]->getBoundingBox()->x, enemyDroneVector[i]->getBoundingBox()->y);
			LC->changePosition(enemyDroneVector[i]->getLightID(), temppos.x, temppos.y);
		}
	}
}
void EnemyDroneCollection::draw() {
	for (int i = 0; i < enemyDroneVector.size(); i++)
	{
		if (enemyDroneVector[i]->getMode() == active && LC->getRadius(enemyDroneVector[i]->getLightID()) < 20) {
			LC->addToRadius(enemyDroneVector[i]->getLightID(), 0.5);
		}
		enemyDroneVector[i]->draw();
	}
}
BoundingBox* EnemyDroneCollection::getBoundingBox(int _index) {
	return enemyDroneVector[_index]->getBoundingBox();
}
void EnemyDroneCollection::remove(int _index) {
	if (enemyDroneVector[_index]->getLightID() != -1) {
		LC->removeLight(enemyDroneVector[_index]->getLightID());
	}
	enemyDroneVector.erase(enemyDroneVector.begin() + _index);
}

int EnemyDroneCollection::getClosestTarget(int _index)
{
	float distance = 1000000;
	int index = -1;
	for (int i = 0; i < targets.size(); i++) {
		if (cd.getDistance(glm::vec2(targets[i]->x + targets[i]->w/2, targets[i]->y + targets[i]->h / 2), enemyDroneVector[_index]->getPosition()) < distance) {
			distance = cd.getDistance(glm::vec2(targets[i]->x + targets[i]->w / 2, targets[i]->y + targets[i]->h), enemyDroneVector[_index]->getPosition());
			index = i;
		}
	}
	return index;
}

void EnemyDroneCollection::addTarget(BoundingBox* _boundingBox) {
	targets.push_back(_boundingBox);
}