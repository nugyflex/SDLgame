#pragma once
#include <vector>
#include <string>
#include "LightCollection.h"
#include "Flare.h"
#include "GlowStick.h"
enum WorldItemType { flare, glowStick, default};
class WorldItemCollection {
public:
	WorldItemCollection();
	~WorldItemCollection();
	void addItem(WorldItemType _type, float x, float y); 
	void addItem(WorldItemType _type, float x, float y, int _lightID);
	void addItem(WorldItemType _type, float x, float y, LightCollection* _lc);
	void drawItems();
	void runItems();
	void linkToLights(LightCollection* _lc);
	int getLightID(int _index) { return worldItemVector[_index]->getLightID(); };
	int getVectorSize() { return worldItemVector.size(); }
	BoundingBox* getBoundingBox(int _index);
private:
	std::vector<WorldItem*> worldItemVector;
};
