#pragma once
#include <GameEngine\BoundingBox.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\SpriteBatch.h>
class Player
{
public:
	Player();
	~Player();
	void init(float _x, float _y);
	BoundingBox* getBoundingBox();
	void handleInput(GameEngine::InputManager* _im);
	void calcNewPos();
	void draw(GameEngine::SpriteBatch* sb);
private:
	BoundingBox boundingBox;
	float vel;
	bool jumpLatch;
};

