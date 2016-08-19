#pragma once
#include <GameEngine\BoundingBox.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\SpriteBatch.h>
#include "Inventory.h"
#include "WorldItemCollection.h"
#include <GameEngine\SpriteSheet.h>
#include "ProjectileCollection.h"
#include <GameEngine\Camera2D.h>
class Player
{
public:
	Player();
	~Player();
	void init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb, GameEngine::DrawText* _drawText, ProjectileCollection* _projectileCollectionPointer);
	BoundingBox* getBoundingBox();
	void handleInput(GameEngine::InputManager* _im, GameEngine::Camera2D* _c);
	void calcNewPos();
	void draw();
	void drawInventory(glm::vec2 _position);
private:
	WorldItemCollection* itemCollectionPointer;
	BoundingBox boundingBox;
	float vel;
	bool jumpLatch;
	bool useLatch;
	GameEngine::SpriteBatch* sb;
	Inventory inventory;
	GameEngine::SpriteSheet walkRight;
	GameEngine::SpriteSheet walkLeft;
	GameEngine::SpriteSheet standRight;
	GameEngine::SpriteSheet standLeft;
	bool lastDirectionRight = true;
	int frame = 0;
	int fs = 0;
	ProjectileCollection* projectileCollectionPointer;
};

