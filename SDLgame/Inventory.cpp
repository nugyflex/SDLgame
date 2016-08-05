#include "Inventory.h"



Inventory::Inventory()
{
}


Inventory::~Inventory()
{
}

void Inventory::addItem(inventoryitemType _type, int _amount) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (storage[i][j].type == _type)
			{
				storage[i][j].amount += _amount;
			}
			if (storage[i][j].type == InventoryNone)
			{
				storage[i][j].type = _type;
				storage[i][j].amount = _amount;
			}
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