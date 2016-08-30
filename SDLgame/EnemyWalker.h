#pragma once
#include <GameEngine\BoundingBox.h>
#include <glm.hpp>
#include <GameEngine\GameEngine.h>
#include "ProjectileCollection.h"
#include "EnemyDrone.h"
class EnemyWalker {
public:
	EnemyWalker::EnemyWalker(float _x, float _y, GameEngine::SpriteBatch* _sb, ProjectileCollection* _pc);
	EnemyWalker::~EnemyWalker();
	BoundingBox* getBoundingBox();
	int getLightID();
	void setLightID(int _ID) { lightID = _ID; }
	void run();
	void ai();
	void calcNewPos();
	void setTarget(float _x, float _y);
	void setTarget(glm::vec2 _target);
	void setPosition(float _x, float _y);
	float getHealth();
	void load();
	void draw();
	void subtractHealth(float _damage);
	glm::vec2 getPosition();
	behaviorType mode;
	behaviorType getMode();
	GameEngine::Light getLight();
	glm::vec2 getLightOffSet();
private:
	glm::vec2 lightOffSet;
	float health;
	GameEngine::Light Light;
	int lightID;
	GameEngine::SpriteBatch* sb;
	ProjectileCollection* pc;
	glm::vec2 target;
	BoundingBox boundingBox;
	float gravity;
	float vel;
};