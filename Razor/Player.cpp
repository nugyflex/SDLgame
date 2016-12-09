#include "Player.h"
#include <SDL.h>

Player::Player(float _x, float _y, float _width, float _height, GameEngine::SpriteBatch* _sb) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = _width;
	boundingBox.h = _height;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	sb = _sb;
}
Player::~Player() {

}
void Player::draw() {
	
}
void Player::handleInput(GameEngine::InputManager* _im) {
	if (_im->isKeyPressed(SDLK_w)) {
		if (_im->isKeyPressed(SDLK_s)) {
			boundingBox.yv = 0;
		}
		else {
			boundingBox.yv = 2;
		}
	}
	else if (_im->isKeyPressed(SDLK_s)) {
		boundingBox.yv = -2;
	}
	if (_im->isKeyPressed(SDLK_a)) {
		if (_im->isKeyPressed(SDLK_d)) {
			boundingBox.xv = 0;
		}
		else {
			boundingBox.xv = -2;
		}
	}
	else if (_im->isKeyPressed(SDLK_d)) {
		boundingBox.xv = 2;
	}
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}