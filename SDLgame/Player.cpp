#include "Player.h"
#include <SDL.h>
#include <GameEngine\GameEngine.h>

Player::Player()
{
}
Player::~Player()
{
}
void Player::init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb) {
	sb = _sb;
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 30;
	boundingBox.h = 30;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	vel = 6;
	jumpLatch = true;
	useLatch = true;
	itemCollectionPointer = _itemCollectionPointer;
	inventory.init(sb);
	inventory.addItem(Inventoryflare, 2);
	inventory.addItem(InventoryGlowStick, 5);
}
BoundingBox* Player::getBoundingBox() {
	return &boundingBox;
}
void Player::handleInput(GameEngine::InputManager* _im) {

	if (_im->isKeyPressed(SDLK_w)) {
		if (jumpLatch && boundingBox.onGround)
		{
			boundingBox.yv = 2*vel;
			jumpLatch = false;
		}
		
	}
	else
	{
		jumpLatch = true;
	}
	boundingBox.onGround = false;
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
	else if (_im->isKeyPressed(SDLK_t)) {
		if (useLatch) {
			if (inventory.removeItem(InventoryGlowStick, 1)) {
				itemCollectionPointer->addItem(glowStick, boundingBox.x, boundingBox.y, boundingBox.xv, boundingBox.yv);
			}
		}
		useLatch = false;
	}
	else {
		useLatch = true;
	}
	boundingBox.yv -= 0.3;
}
void Player::calcNewPos() {
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
void Player::draw() {
	GameEngine::Color color;

	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = 255;
	if (boundingBox.onGround)
	{
		color.r = 255;
		color.g = 90;
		color.b = 90;
		color.a = 255;
	}
	GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
}
void Player::drawInventory(glm::vec2 _position) {
	inventory.draw(_position.x, _position.y);
}