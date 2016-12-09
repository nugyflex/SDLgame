#pragma once
#include <GameEngine\BoundingBox.h>
#include <glm.hpp>
#include <GameEngine\InputManager.h>
#include <GameEngine\SpriteBatch.h>
class Player {
public:
	Player(float _x, float _y, float _width, float _height, GameEngine::SpriteBatch* _sb);
	~Player();
	void draw();
	BoundingBox boundingBox;
	void handleInput(GameEngine::InputManager* _im);
private:
	GameEngine::SpriteBatch* sb;
};