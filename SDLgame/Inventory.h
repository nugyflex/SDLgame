#pragma once

#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
#include <GameEngine\GLTexture.h>
#include <GameEngine\DrawText.h>

#include "InventoryItem.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
	void init(GameEngine::SpriteBatch * _sb, GameEngine::DrawText* _drawText);
	void addItem(inventoryitemType _type, int _amount);
	bool removeItem(inventoryitemType _type, int _amount);
	void draw(float _x, float _y);
protected:
	InventoryItem storage[4][4];
	InventoryItem hotBar[4];
	GameEngine::SpriteBatch * sb;
	int cellDrawSize;
	void drawItem(InventoryItem Item, float _x, float _y);
	GameEngine::GLTexture flareTexture;
	GameEngine::GLTexture glowStickTexture;
	GameEngine::DrawText* drawText;
};