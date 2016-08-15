#pragma once
#include <vector>
#include <string>
#include "LightCollection.h"
#include "Flare.h"
#include "GlowStick.h"
#include "Explosion.h"
class WorldItemCollection {
public:
	WorldItemCollection();
	~WorldItemCollection();
	void init(LightCollection* _LC, GameEngine::SpriteBatch* _sb);
	void addItem(WorldItemType _type, float x, float y); 
	void addItem(WorldItemType _type, float x, float y, float xv, float yy);
	void addItem(WorldItemType _type, float x, float y, int _lightID);
	void drawItems();
	void runItems();
	void linkToLights();
	int getLightID(int _index) { return worldItemVector[_index]->getLightID(); };
	int getVectorSize() { return worldItemVector.size(); }
	BoundingBox* getBoundingBox(int _index);
	void remove(int _index);
private:
	std::vector<WorldItem*> worldItemVector;
	LightCollection* LC;
	GameEngine::SpriteBatch* sb;
};
