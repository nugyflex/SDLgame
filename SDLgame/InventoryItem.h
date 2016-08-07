#pragma once
enum inventoryitemType { InventoryFlare, InventoryGlowStick, InventoryNone };
class InventoryItem
{
public:
	inventoryitemType type;
	int amount;
	InventoryItem();
	~InventoryItem();
};