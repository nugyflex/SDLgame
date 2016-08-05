#include "Player.h"
#include <SDL.h>
#include <GameEngine\GameEngine.h>

Player::Player()
{
}
Player::~Player()
{
}
void Player::init(float _x, float _y, WorldItemCollection* _itemCollectionPointer) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 30;
	boundingBox.h = 30;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	vel = 3;
	jumpLatch = true;
	useLatch = true;
	itemCollectionPointer = _itemCollectionPointer;
	inventory.addItem(Inventoryflare, 5);
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
	if (_im->isKeyPressed(SDLK_r)) {
		if (useLatch) {
			if (inventory.removeItem(Inventoryflare, 1)) {
				itemCollectionPointer->addItem(flare, boundingBox.x, boundingBox.y, boundingBox.xv, boundingBox.yv);
			}
		}
		useLatch = false;
	}
	else {
		useLatch = true;
	}
}
void Player::calcNewPos() {
	boundingBox.yv -= 0.15;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
void Player::draw(GameEngine::SpriteBatch* sb) {
	GameEngine::Color color;
	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = 255;
	GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, color, sb);
}