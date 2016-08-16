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
	void draw();
	void calcNewPos(float _x, float _y);
	void subtractHealth(int _amount);
	int getHealth();
	void setMode(behaviorType _mode);
	bool getFiring();
	glm::vec3 getLaserColour();
	behaviorType getBehaviorType();
private:
	BoundingBox boundingBox;
	GameEngine::SpriteSheet spriteSheet;
	int health;
	float speed;
	behaviorType mode;
	int nextPatrolIndex;
	float hoverVel;
	bool firing;
	int shootCooldown;
	int maxShootCooldown;
	glm::vec3 laserColour;
	GameEngine::SpriteBatch* sb;
};