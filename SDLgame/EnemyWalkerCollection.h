#pragma once
#pragma once

#include <vector>

#include "GameEngine/CollisionDetection.h"
#include "GameEngine/Camera2D.h"

#include "EnemyWalker.h"
#include "WorldItemCollection.h"

class EnemyWalkerCollection {
public:
	EnemyWalkerCollection();
	~EnemyWalkerCollection();
	void init(GameEngine::SpriteBatch* _sb, WorldItemCollection* _worldItems, GameEngine::Camera2D* _camera, LightCollection* _LC, ProjectileCollection* _pc);
	void add(float x, float y);
	void addTarget(BoundingBox* _boundingBox);
	void draw();
	void run();
	EnemyWalker* getWalker(int _index);
	void reduceHealth(int _index, float _health);
	void linkToLights();
	int getVectorSize() { return enemyWalkerVector.size(); }
	BoundingBox* getBoundingBox(int _index);
private:
	void remove(int _index);
	std::vector<EnemyWalker*> enemyWalkerVector;
	std::vector<BoundingBox*> targets;
	int getClosestTarget(int _index);
	GameEngine::SpriteBatch* sb;
	GameEngine::CollisionDetection cd;
	WorldItemCollection* worldItems;
	GameEngine::Camera2D* camera;
	LightCollection* LC;
	ProjectileCollection* pc;
};
