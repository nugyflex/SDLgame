#pragma once
#include <GameEngine\SpriteSheet.h>
class Fire {
public:
	Fire();
	Fire(GameEngine::SpriteBatch* _sb, int _x, int _y);
	~Fire();
	void draw();
	void draw(int _x, int _y);
	void extinguish(float _amount);
	bool isExtinguished();
	float health;
private:
	glm::vec2 position;
	GameEngine::SpriteBatch* sb;
	GameEngine::SpriteSheet animation;
};