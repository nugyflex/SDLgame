#pragma once

#include "GameEngine/SpriteSheet.h"
#include "GameEngine/SpriteBatch.h"
#include <GameEngine/BoundingBox.h>
#include <GameEngine/GameEngine.h>

#include "ProjectileCollection.h"

enum behaviorType { active, inactive };
enum hoverDirection { up, down };
class EnemyDrone {

public:
	EnemyDrone();
	EnemyDrone(float x, float y, GameEngine::SpriteBatch* _sb, ProjectileCollection* _pc);
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
	int getLightID();
	GameEngine::Light getLight();
	glm::vec2 getLightOffSet();;
	void setLightID(int _ID) { lightID = _ID; }
	behaviorType getMode();
	void attack();
private:
	GameEngine::Light Light;
	int lightID;
	glm::vec2 lightOffset;
	BoundingBox boundingBox;
	GameEngine::SpriteSheet spriteSheet;
	float hoverY;
	float hoverVel;
	int health;
	float vel;
	behaviorType mode;
	int shootCooldown;
	int maxShootCooldown;
	hoverDirection hoverDir;
	GameEngine::SpriteBatch* sb;
	glm::vec2 target;
	glm::vec2 spriteSheetOffSet;
	glm::vec2 lightOffSet;
	ProjectileCollection* pc;
};