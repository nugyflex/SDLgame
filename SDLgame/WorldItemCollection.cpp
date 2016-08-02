#include "WorldItemCollection.h"
WorldItemCollection::WorldItemCollection(){}
WorldItemCollection::~WorldItemCollection(){}
void WorldItemCollection::addItem(WorldItemType _type, float _x, float _y, int _lightID) {
	switch (_type)
	{ 
	case flare:
		worldItemVector.push_back(Flare());
		break;
	case default:
		break;
	}
	worldItemVector[worldItemVector.size() - 1].init(0, 0, 10, 10);
	worldItemVector[worldItemVector.size() - 1].setPosition(glm::vec2(_x, _y));
	worldItemVector[worldItemVector.size() - 1].setLightID(_lightID);
}
void WorldItemCollection::runItems() {
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		worldItemVector[i].run();
	}
}
void WorldItemCollection::linkToLights(LightCollection* _lc)
{
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		glm::vec2 temppos = worldItemVector[i].getLightOffset() + worldItemVector[i].getPosition();
		_lc->changePosition(worldItemVector[i].getLightID(), temppos.x, temppos.y);
	}
}
glm::vec4 WorldItemCollection::getRect(int _index) {
	return worldItemVector[_index].getRect();
}