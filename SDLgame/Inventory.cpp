
#include <GameEngine\ResourceManager.h>

#include "Inventory.h"

Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
void Inventory::init(GameEngine::SpriteBatch * _sb, GameEngine::DrawText* _drawText) {
	sb = _sb;
	drawText = _drawText;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			storage[i][j].type = InventoryNone;
			storage[i][j].amount = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		hotBar[i].type = InventoryNone;
		hotBar[i].amount = 0;
	}
	cellDrawSize = 100;
	flareTexture = GameEngine::ResourceManager::getTexture("Textures/flareIcon.png");
	glowStickTexture = GameEngine::ResourceManager::getTexture("Textures/glowStickIcon.png");
}
void Inventory::addItem(inventoryitemType _type, int _amount) {
	bool finished = false;
	for (int i = 0; i < 4; i++) {
		if (!finished) {
			for (int j = 0; j < 4; j++) {
				if (!finished) {
					if (storage[i][j].type == _type)
					{
						storage[i][j].amount += _amount;
						finished = true;
					}
					if (storage[i][j].type == InventoryNone)
					{
						storage[i][j].type = _type;
						storage[i][j].amount = _amount;
						finished = true;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
}
bool Inventory::removeItem(inventoryitemType _type, int _amount) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (storage[i][j].type == _type)
			{
				if (storage[i][j].amount < _amount) {
					return false;
				}
				else {
					storage[i][j].amount -= _amount;
					if (storage[i][j].amount == 0) {
						storage[i][j].type = InventoryNone;
					}
					return true;
				}
			}

		}
	}
	return false;
}
void Inventory::draw(float _x, float _y) {
	_x = _x - (4 * cellDrawSize) / 2;
	_y = _y - (4 * cellDrawSize) / 2;
	GameEngine::Color color;
	color.r = 120;
	color.g = 200;
	color.b = 120;
	color.a = 70;
	GameEngine::drawRect(_x - 2, _y - 2, cellDrawSize * 4 + 5, cellDrawSize * 4 + 5, 0, color, sb);
	color.r = 120;
	color.g = 200;
	color.b = 120;
	color.a = 120;
	for (int i = 0; i < 5; i++) {
		GameEngine::drawRect(_x + (cellDrawSize * i), _y, 1, cellDrawSize * 4 + 1, 0, color, sb);
	}
	for (int i = 0; i < 5; i++) {
		GameEngine::drawRect(_x, _y + (cellDrawSize * i), cellDrawSize * 4 + 1, 1, 0, color, sb);
	}
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (storage[i][j].amount>0) {
				drawText->draw(_x + cellDrawSize * i + 7, _y + cellDrawSize * j + 7, storage[i][j].amount, 2);
			}
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + 3, cellDrawSize - 5, 1, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + 3, 1, cellDrawSize - 5, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + cellDrawSize - 3, _y + cellDrawSize * j + 3, 1, cellDrawSize - 5, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + cellDrawSize - 3, cellDrawSize - 5, 1, 0, color, sb);
			drawItem(storage[i][j], _x + cellDrawSize * i + (cellDrawSize - 40) / 2, _y + cellDrawSize * j + (cellDrawSize - 40) / 2);
		}
	}
}
void Inventory::drawItem(InventoryItem _item, float _x, float _y) {
	int textureID;
	bool draw = true;
	switch (_item.type) {
		case InventoryFlare:
			textureID = flareTexture.id;
			break;
		case InventoryGlowStick:
			textureID = glowStickTexture.id;
			break;
		case InventoryNone:
			draw = false;
			break;
	}
	if (draw)
	{
		GameEngine::Color color;
		color.r = 255;
		color.g = 0;
		color.b = 255;
		color.a = 255;
		sb->draw(glm::vec4(_x, _y, 40, 40), glm::vec4(0, 0, 1, 1), textureID, 0.0f, color, 0);
	}
}