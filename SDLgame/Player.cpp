#include "Player.h"
#include <SDL.h>
#include <GameEngine\GameEngine.h>
#include <iostream>

Player::Player()
{
}
Player::~Player()
{
}
void Player::init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb, GameEngine::DrawText* _drawText) {
	sb = _sb;
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 10;
	boundingBox.h = 50;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	vel = 4;
	jumpLatch = true;
	useLatch = true;
	itemCollectionPointer = _itemCollectionPointer;
	inventory.init(sb, _drawText);
	inventory.addItem(InventoryFlare, 2);
	inventory.addItem(InventoryGlowStick, 5);
	walkRight.init(sb, 13, 25, 2, 8, 6, -5, 0);
	walkRight.loadTexture("textures/player_walk_right.png");
	walkLeft.init(sb, 13, 25, 2, 8, 6, -4, 0);
	walkLeft.loadTexture("textures/player_walk_left.png");
	standRight.init(sb, 10, 25, 2, 1, 1, -4, 0);
	standRight.loadTexture("textures/player_standing_right.png");
	standLeft.init(sb, 10, 25, 2, 1, 1, -1, 0);
	standLeft.loadTexture("textures/player_standing_left.png");
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
				if (inventory.removeItem(InventoryFlare, 1)) {
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
	
}
void Player::calcNewPos() {


	if (sqrt(pow(boundingBox.x - 400, 2) + pow(boundingBox.y - 3400, 2)) > 100) {
		float theta = atan(-1 * (3400 - boundingBox.y) / (400 - boundingBox.x));
		if (400 >= boundingBox.x) {
			boundingBox.yv = sin(theta) * -1 * vel;
			boundingBox.xv = cos(theta) * vel;
		}
		else {
			boundingBox.yv = sin(theta) * vel;
			boundingBox.xv = cos(theta) * -1 * vel;
		}
		//boundingBox.xv *= -1;
		//boundingBox.yv *= -1;
	}
	boundingBox.yv -= 0.5;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
void Player::draw() {
	if (boundingBox.xv > 0) {
		lastDirectionRight = true;
		walkRight.run();
		walkRight.draw(boundingBox.x, boundingBox.y);
	}
	else {
		walkRight.reset();
		if (boundingBox.xv < 0) {
			lastDirectionRight = false;
			walkLeft.run();
			walkLeft.draw(boundingBox.x, boundingBox.y);
		}
		else {
			walkLeft.reset();
			if (boundingBox.xv == 0) {
				if (lastDirectionRight) {
					standRight.draw(boundingBox.x, boundingBox.y);
				}
				else {
					standLeft.draw(boundingBox.x, boundingBox.y);
				}
			}
		}
	}

	//GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
	//sb->draw(glm::vec4(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h), glm::vec4((1.0f / 8.0f)*frame, 0, 1.0f/8.0f, 1), texture.id, 1, color, 1);
}
void Player::drawInventory(glm::vec2 _position) {
	GameEngine::Color color;
	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = 255;
	inventory.draw(_position.x, _position.y);
	
}
