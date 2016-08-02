#pragma once
#include "Flare.h"
#include <vector>
#include <string>
#include "LightCollection.h"
enum WorldItemType { flare, default};
class WorldItemCollection {
public:
	WorldItemCollection();
	~WorldItemCollection();
	void addItem(WorldItemType _type, float x, float y);
	void addItem(WorldItemType _type, float x, float y, int _lightID);
	void drawItems();
	void runItems();
	void linkToLights(LightCollection* _lc);
	glm::vec4 getRect(int _index);
private:
	std::vector<WorldItem> worldItemVector;
};
