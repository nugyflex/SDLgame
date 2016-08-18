#pragma once

#include <GameEngine\SpriteBatch.h>
class Projectile {
public:
	Projectile();
	~Projectile();
	void init(GameEngine::SpriteBatch* _sb, float _x, float _y, float _xVel, float _yVel);
	void calcNewPos();
	void run();
	void draw();
private:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 lastPosition;
	glm::vec2 drawPosition;
	GameEngine::SpriteBatch* sb;
};