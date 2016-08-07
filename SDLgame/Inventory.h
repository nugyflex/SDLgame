#pragma once
#include "InventoryItem.h"
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
class Inventory
{
public:
	Inventory();
	~Inventory();
	void init(GameEngine::SpriteBatch * _sb);
	void addItem(inventoryitemType _type, int _amount);
	bool removeItem(inventoryitemType _type, int _amount);
	void draw(float _x, float _y);
protected:
	InventoryItem storage[4][4];
	InventoryItem hotBar[4];
	GameEngine::SpriteBatch * sb;
	int cellDrawSize;
	void drawItem(InventoryItem Item, float _x, float _y);
};