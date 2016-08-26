#pragma once

#include <vector>

#include "GameEngine/CollisionDetection.h"
#include "GameEngine/Camera2D.h"

#include "EnemyDrone.h"
#include "WorldItemCollection.h"

class EnemyDroneCollection {
public:
	EnemyDroneCollection();
	~EnemyDroneCollection();
	void init(GameEngine::SpriteBatch* _sb, WorldItemCollection* _worldItems, GameEngine::Camera2D* _camera, LightCollection* _LC, ProjectileCollection* _pc);
	void add(float x, float y);
	void addTarget(BoundingBox* _boundingBox);
	void draw();
	void run();
	EnemyDrone* getDrone(int _index);
	void reduceHealth(int _index, float _health);
	void linkToLights();
	int getVectorSize() { return enemyDroneVector.size(); }
	BoundingBox* getBoundingBox(int _index);
private:
	void remove(int _index);
	std::vector<EnemyDrone*> enemyDroneVector;
	std::vector<BoundingBox*> targets;
	int getClosestTarget(int _index);
	GameEngine::SpriteBatch* sb;
	GameEngine::CollisionDetection cd;
	WorldItemCollection* worldItems;
	GameEngine::Camera2D* camera;
	LightCollection* LC;
	ProjectileCollection* pc;
};
