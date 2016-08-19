#pragma once

#include <GameEngine\SpriteBatch.h>

class Projectile {
public:
	Projectile();
	~Projectile();
	void init(GameEngine::SpriteBatch* _sb, float _x, float _y, float _xVel, float _yVel);
	void calcNewPos();
	glm::vec2 getPosition() { return position; }
	glm::vec2 getLastPosition() { return lastPosition; }
	void run();
	void draw();
	bool toDelete;
	void setPosition(glm::vec2 _position);
private:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 lastPosition;
	glm::vec2 drawPosition;
	GameEngine::SpriteBatch* sb;
};