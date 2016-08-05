#pragma once
enum inventoryitemType { Inventoryflare, InventoryGlowStick, InventoryNone };
class InventoryItem
{
public:
	inventoryitemType type;
	int amount;
	InventoryItem();
	~InventoryItem();
};