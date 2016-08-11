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
	boundingBox.w = 26;
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
	texture = GameEngine::ResourceManager::getTexture("Textures/player_walk_right.png");
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
	boundingBox.yv -= 0.5;
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
	fs++;
	if (fs == 5) {
		fs = 0;
	}
	if (fs == 0)
	{
		frame++;
		if (frame == 9) {
			frame = 0;
		}
	}
	//GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
	sb->draw(glm::vec4(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h), glm::vec4((1.0f / 8.0f)*frame, 0, 1.0f/8.0f, 1), texture.id, 1, color, 1);
}
void Player::drawInventory(glm::vec2 _position) {
	GameEngine::Color color;
	color.r = 150;
	color.g = 150;
	color.b = 150;
	color.a = 255;
	inventory.draw(_position.x, _position.y);
	
}
void Player::runAnimation() {
	
}