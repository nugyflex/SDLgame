#pragma once
#include <GameEngine\SpriteSheet.h>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\BoundingBox.h>

enum behaviorType { active, inactive };
class EnemyDrone {

public:
	EnemyDrone();
	EnemyDrone(float x, float y, GameEngine::SpriteBatch* _sb);
	~EnemyDrone();
	void load();
	void run();
	void setPosition(float _x, float _y);
	void setTarget(float _x, float _y);
	void setTarget(glm::vec2 _target);
	void draw();
	void calcNewPos(float _x, float _y);
	void subtractHealth(int _amount);
	int getHealth();
	void setMode(behaviorType _mode);
	BoundingBox* getBoundingBox();
	glm::vec2 getPosition();
private:
	BoundingBox boundingBox;
	GameEngine::SpriteSheet spriteSheet;
	int health;
	float vel;
	behaviorType mode;
	int shootCooldown;
	int maxShootCooldown;
	GameEngine::SpriteBatch* sb;
	glm::vec2 target;
};