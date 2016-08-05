#pragma once
#include "InventoryItem.h"
class Inventory
{
public:
	Inventory();
	~Inventory();
	void addItem(inventoryitemType _type, int _amount);
	bool removeItem(inventoryitemType _type, int _amount);
protected:
	InventoryItem storage[4][4];
	InventoryItem hotBar[4];
};

