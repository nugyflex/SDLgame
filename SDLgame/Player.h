#pragma once
#include <GameEngine\BoundingBox.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\SpriteBatch.h>
#include "Inventory.h"
#include "WorldItemCollection.h"
class Player
{
public:
	Player();
	~Player();
	void init(float _x, float _y, WorldItemCollection* _itemCollectionPointer, GameEngine::SpriteBatch* _sb, GameEngine::DrawText* _drawText);
	BoundingBox* getBoundingBox();
	void handleInput(GameEngine::InputManager* _im);
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
};

