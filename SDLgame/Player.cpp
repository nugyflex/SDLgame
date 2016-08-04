#include "Player.h"
#include <SDL.h>
#include <GameEngine\GameEngine.h>

Player::Player()
{
}
Player::~Player()
{
}
void Player::init(float _x, float _y) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 10;
	boundingBox.h = 10;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	vel = 4;
	jumpLatch = true;
}
BoundingBox* Player::getBoundingBox() {
	return &boundingBox;
}
void Player::handleInput(GameEngine::InputManager* _im) {

	if (_im->isKeyPressed(SDLK_w)) {
		if (jumpLatch)
		{
			boundingBox.yv = 2*vel;
		}
		jumpLatch = false;
	}
	else
	{
		jumpLatch = true;
	}
	if (_im->isKeyPressed(SDLK_a)) {
		boundingBox.xv = -vel;
	}
	else
	{
		boundingBox.xv = 0;
	}
	if (_im->isKeyPressed(SDLK_s)) {
		//boundingBox.yv = -vel;
	}
	if (_im->isKeyPressed(SDLK_d)) {
		boundingBox.xv = vel;
	}
}
void Player::calcNewPos() {
	boundingBox.yv -= 0.3;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
void Player::draw(GameEngine::SpriteBatch* sb) {
	GameEngine::Color color;
	color.r = 100;
	color.g = 100;
	color.b = 100;
	color.a = 255;
	GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, color, sb);
}