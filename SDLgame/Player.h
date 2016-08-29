#pragma once

#include <GameEngine\BoundingBox.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\SpriteSheet.h>
#include <GameEngine\Camera2D.h>

#include "Inventory.h"
#include "WorldItemCollection.h"
#include "ProjectileCollection.h"

class Player
{
public:
	Player();
	~Player();
	void init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb, GameEngine::DrawText* _drawText, ProjectileCollection* _projectileCollectionPointer, GameEngine::CollisionDetection* _cd, GameEngine::Camera2D* _c);
	BoundingBox* getBoundingBox();
	void handleInput(GameEngine::InputManager* _im);
	void calcNewPos();
	void draw();
	void drawInventory(glm::vec2 _position);
	void reduceHealth(int _damage);
	glm::vec2 shield1;
	glm::vec2 shield2;
private:
	GameEngine::Camera2D* camera;
	WorldItemCollection* itemCollectionPointer;
	GameEngine::SpriteBatch* sb;
	ProjectileCollection* projectileCollectionPointer;
	GameEngine::CollisionDetection* cd;
	BoundingBox boundingBox;
	float vel;
	bool jumpLatch;
	bool useLatch;

	Inventory inventory;

	GameEngine::SpriteSheet walkRight;
	GameEngine::SpriteSheet walkLeft;
	GameEngine::SpriteSheet standRight;
	GameEngine::SpriteSheet standLeft;
	GameEngine::SpriteSheet landingLeft;
	GameEngine::SpriteSheet landingRight;
	GameEngine::SpriteSheet jumpingLeft;
	GameEngine::SpriteSheet jumpingRight;
	GameEngine::SpriteSheet laserGun;
	GameEngine::GLTexture shieldTexture;

	glm::vec2 mouseCoords;
	float gunAngle;
	float lastyv;
	int landingAnimation = 0;
	glm::vec2 shieldSize;
	glm::vec2 shieldTexturePos;
	glm::vec2 shieldTextureVel;
	bool lastDirectionRight = true;
	int frame = 0;
	int fs = 0;
	float health;
	float shieldLength;
	float shieldDistance;
	float shieldAngle;
	
};

