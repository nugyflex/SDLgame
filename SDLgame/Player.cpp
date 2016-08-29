
#include <SDL.h>

#include "Player.h"

Player::Player()
{
}
Player::~Player()
{
}
void Player::init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb, GameEngine::DrawText* _drawText, ProjectileCollection* _projectileCollectionPointer, GameEngine::CollisionDetection* _cd, GameEngine::Camera2D* _c) {
	sb = _sb;
	camera = _c;
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = 10;
	boundingBox.h = 50;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	vel = 4;
	health = 10;
	jumpLatch = true;
	useLatch = true;
	itemCollectionPointer = _itemCollectionPointer;
	projectileCollectionPointer = _projectileCollectionPointer;
	inventory.init(sb, _drawText);
	inventory.addItem(InventoryFlare, 20);
	inventory.addItem(InventoryGlowStick, 50);
	walkRight.init(sb, 13, 25, 2, 8, 6, -5, 0);
	walkRight.loadTexture("textures/player_walk_right2.png");
	walkLeft.init(sb, 13, 25, 2, 8, 6, -4, 0);
	walkLeft.loadTexture("textures/player_walk_left2.png");
	standRight.init(sb, 10, 25, 2, 1, 1, -4, 0);
	standRight.loadTexture("textures/player_standing_right.png");
	standLeft.init(sb, 10, 25, 2, 1, 1, -1, 0);
	standLeft.loadTexture("textures/player_standing_left.png");
	landingRight.init(sb, 10, 25, 2, 3, 6, -4, 0);
	landingRight.loadTexture("textures/player_land_right.png");
	landingLeft.init(sb, 10, 25, 2, 3, 6, -1, 0);
	landingLeft.loadTexture("textures/player_land_left.png");
	jumpingLeft.init(sb, 13, 25, 2, 1, 6, -4, 0);
	jumpingLeft.loadTexture("textures/player_jumping_left.png");
	jumpingRight.init(sb, 13, 25, 2, 1, 6, -5, 0);
	jumpingRight.loadTexture("textures/player_jumping_right.png");
	laserGun.init(sb, 17, 5, 2, 1, 6, 0, 0);
	laserGun.loadTexture("textures/laserPistolInHand.png");
	shieldTexture = GameEngine::ResourceManager::getTexture("textures/shieldTexture.png");
	shieldSize = glm::vec2(60, 5);
	shieldLength = shieldSize.x;
	shieldDistance = 60;
	shieldAngle = 0;
	shieldTexturePos = glm::vec2(0, 0);
	shieldTextureVel = glm::vec2(0.35, 0.15);
}
BoundingBox* Player::getBoundingBox() {
	return &boundingBox;
}
void Player::handleInput(GameEngine::InputManager* _im) {

	if (_im->isKeyPressed(SDLK_w)) {
		if (landingAnimation <= 0) {
			if (jumpLatch && boundingBox.onGround)
			{
				boundingBox.yv = 2 * vel;
				jumpLatch = false;
			}
		}
	}
	else
	{
		jumpLatch = true;
	}
	if (_im->isKeyPressed(SDLK_a) && _im->isKeyPressed(SDLK_d) || landingAnimation > 0)
	{
		boundingBox.xv *= 0.75;
	}
	else if (_im->isKeyPressed(SDLK_a)) {
		if (boundingBox.xv > -vel) {
			boundingBox.xv += -vel / 6;
		}
		else if (boundingBox.xv > 0)
		{
			boundingBox.xv = - vel / 6;
		}
	}
	else if (_im->isKeyPressed(SDLK_d)) {
		if (boundingBox.xv < vel) {
			boundingBox.xv += vel / 6;
		}
		else if (boundingBox.xv < 0)
		{
			boundingBox.xv = vel / 6;
		}
	}
	else if (boundingBox.onGround)
	{
		boundingBox.xv *= 0.75;
	}
	else
	{
		boundingBox.xv *= 0.95;
	}
	boundingBox.onGround = false;
	if (_im->isKeyPressed(SDLK_s)) {
		//boundingBox.yv = -vel;
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
	if (_im->isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _im->getMouseCoords();
		mouseCoords = camera->convertScreenToWorld(mouseCoords);
		if (!_im->lastMouseL) {
			if (lastDirectionRight)
			{
				projectileCollectionPointer->launch(glm::vec2(boundingBox.x + 3, boundingBox.y + 33), glm::vec2(mouseCoords.x, -mouseCoords.y), 30, damageDrone);
			}
			else
			{
				projectileCollectionPointer->launch(glm::vec2(boundingBox.x + 6, boundingBox.y + 33), glm::vec2(mouseCoords.x, -mouseCoords.y), 30, damageDrone);
			}
			//projectileCollectionPointer->launch(glm::vec2(boundingBox.x, boundingBox.y), glm::vec2(mouseCoords.x, -mouseCoords.y), 30, damageDrone);
		}
	}
	mouseCoords = _im->getMouseCoords();
	mouseCoords = camera->convertScreenToWorld(mouseCoords);
	mouseCoords.y *= -1;
	float theta = atan((mouseCoords.x - (boundingBox.x + boundingBox.w / 2)) /  (mouseCoords.y - (boundingBox.y + boundingBox.h / 2)));
	if (mouseCoords.y <= boundingBox.y + boundingBox.h / 2) {
		theta += 3.1415;
	}
	float alpha = theta - 3.1415 / 2;// atan((mouseCoords.y - (boundingBox.y + boundingBox.h / 2)) / -(mouseCoords.x - (boundingBox.x + boundingBox.w / 2)));
	shieldAngle = alpha;
	//shield1 = glm::vec2(shieldDistance * sin(theta) + (boundingBox.x + boundingBox.w / 2) + sin(alpha)*shieldLength / 2, shieldDistance * cos(theta) + (boundingBox.y + boundingBox.h / 2) + cos(alpha)*shieldLength / 2);
	//shield2 = glm::vec2(shieldDistance * sin(theta) + (boundingBox.x + boundingBox.w / 2) - sin(alpha)*shieldLength / 2, shieldDistance * cos(theta) + (boundingBox.y + boundingBox.h / 2) - cos(alpha)*shieldLength / 2);
}
void Player::calcNewPos() {
	boundingBox.yv -= 0.5;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
void Player::draw() {
	if (lastDirectionRight)
	{
		float angle = cd->getAngle(glm::vec2(boundingBox.x + 3, boundingBox.y + 33), mouseCoords) - 3.1415 / 2;
		if (cd->getAngle(glm::vec2(boundingBox.x + 3, boundingBox.y + 33), mouseCoords) < 3.1415)
		{
			laserGun.draw(boundingBox.x + 3, boundingBox.y + 33, cd->getAngle(glm::vec2(boundingBox.x + 3, boundingBox.y + 33), mouseCoords) - 3.1415 / 2, false);
		}
		else
		{
			laserGun.draw(boundingBox.x + 3, boundingBox.y + 33, 3.1415*0.5, false);
		}
	}
	else
	{
		float angle = cd->getAngle(glm::vec2(boundingBox.x + 6, boundingBox.y + 33), mouseCoords) - 3.1415 / 2;
		if (cd->getAngle(glm::vec2(boundingBox.x + 6, boundingBox.y + 33), glm::vec2(mouseCoords.x, boundingBox.y + 33 - (mouseCoords.y - boundingBox.y + 33))) > 3.1415)
		{
			laserGun.draw(boundingBox.x + 6, boundingBox.y + 33, 2 * 3.1415 - (cd->getAngle(glm::vec2(boundingBox.x + 6, boundingBox.y + 33), mouseCoords) + 3.1415 / 2), true);
		}
		else
		{
			laserGun.draw(boundingBox.x + 6, boundingBox.y + 33, 3.1415*0.5, true);
		}
	}
	if (boundingBox.xv > 0)
	{
		lastDirectionRight = true;
	}
	else if (boundingBox.xv < 0)
	{
		lastDirectionRight = false;
	}
	if (lastyv < -15 && boundingBox.yv >= -0.5) {
		landingAnimation = 6 * 3;
		itemCollectionPointer->addItem(dustCloudLanding, boundingBox.x-10, boundingBox.y);
		camera->setScreenShakeIntensity(4);
	}
	else if (lastyv < -10 && boundingBox.yv >= -0.5) {
		landingAnimation = 6;
		camera->setScreenShakeIntensity(2);
	}
	if (landingAnimation > 0)
	{
		if (lastDirectionRight) {
			landingRight.run();
			landingRight.draw(boundingBox.x, boundingBox.y);
		}
		else {
			landingLeft.run();
			landingLeft.draw(boundingBox.x, boundingBox.y);
		}
		landingAnimation--;
	}
	else if (!boundingBox.onGround)
	{
		if (!lastDirectionRight)
		{
			jumpingLeft.draw(boundingBox.x, boundingBox.y);
		}
		else
		{
			jumpingRight.draw(boundingBox.x, boundingBox.y);
		}
	}
	else if (boundingBox.xv > vel*0.7) {
		walkRight.run();
		walkRight.draw(boundingBox.x, boundingBox.y);
	}
	else {
		walkRight.reset();
		if (boundingBox.xv < -vel*0.7) {
			walkLeft.run();
			walkLeft.draw(boundingBox.x, boundingBox.y);
		}
		else {
			walkLeft.reset();
			if (boundingBox.xv > -vel*0.7 && boundingBox.xv < vel*0.7) {
				if (lastDirectionRight) {
					standRight.draw(boundingBox.x, boundingBox.y);
				}
				else {
					standLeft.draw(boundingBox.x, boundingBox.y);
				}
			}
		}
	}

	lastyv = boundingBox.yv;
	//sb->drawLine(shield1, shield2, 10, 255, 10, 255, 1);
	shieldTexturePos += shieldTextureVel;
	//sb->draw(glm::vec4(shield2.x, shield2.y, shieldSize.x, shieldSize.y), glm::vec4(shieldTexturePos.x / 50, shieldTexturePos.y/50, (shieldSize.x/1)/50, (shieldSize.y/1)/50), shieldTexture.id, 1, 0 , shieldAngle + 3.1415 / 2 + 3.1415);
	//GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
	//sb->draw(glm::vec4(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h), glm::vec4((1.0f / 8.0f)*frame, 0, 1.0f/8.0f, 1), texture.id, 1, color, 1);
}
void Player::drawInventory(glm::vec2 _position) {
	inventory.draw(_position.x, _position.y);
}

void Player::reduceHealth(int _damage)
{
	health -= _damage;
}
