#include "Inventory.h"



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}
void Inventory::init(GameEngine::SpriteBatch * _sb) {
	sb = _sb;
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
}
void Inventory::draw(float _x, float _y) {
	GameEngine::Color color;
	color.r = 120;
	color.g = 200;
	color.b = 120;
	color.a = 100;
	for (int i = 0; i < 5; i++) {
		GameEngine::drawRect(_x + (cellDrawSize * i), _y, 1, cellDrawSize * 4 + 1, 0, color, sb);
	}
	for (int i = 0; i < 5; i++) {
		GameEngine::drawRect(_x, _y + (cellDrawSize * i), cellDrawSize * 4 + 1, 1, 0, color, sb);
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + 3, cellDrawSize - 5, 1, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + 3, 1, cellDrawSize - 5, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + cellDrawSize - 3, _y + cellDrawSize * j + 3, 1, cellDrawSize - 5, 0, color, sb);
			GameEngine::drawRect(_x + cellDrawSize * i + 3, _y + cellDrawSize * j + cellDrawSize - 3, cellDrawSize - 5, 1, 0, color, sb);
		}
	}
}