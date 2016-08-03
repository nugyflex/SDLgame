#include "WorldItemCollection.h"
WorldItemCollection::WorldItemCollection(){}
WorldItemCollection::~WorldItemCollection(){}
void WorldItemCollection::addItem(WorldItemType _type, float _x, float _y, LightCollection* _lc) {
	int lightID = 0;
	GameEngine::Light tempLight;
	switch (_type)
	{ 
	case flare:
		worldItemVector.push_back(new Flare());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = _lc->addLight(tempLight);
		break;
	case glowStick:
		worldItemVector.push_back(new GlowStick());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = _lc->addLight(tempLight);
		break;
	case default:
		
		break;
	}
	worldItemVector[worldItemVector.size() - 1]->init(0, 0, 10, 10);
	worldItemVector[worldItemVector.size() - 1]->setPosition(_x, _y);
	worldItemVector[worldItemVector.size() - 1]->setLightID(lightID);
}
void WorldItemCollection::runItems() {
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		worldItemVector[i]->run();
	}
}
void WorldItemCollection::linkToLights(LightCollection* _lc)
{
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		glm::vec2 temppos = worldItemVector[i]->getLightOffset() + glm::vec2(worldItemVector[i]->getBoundingBox()->x, worldItemVector[i]->getBoundingBox()->y);
		_lc->changePosition(worldItemVector[i]->getLightID(), temppos.x, temppos.y);
	}
}
BoundingBox* WorldItemCollection::getBoundingBox(int _index) {
	return worldItemVector[_index]->getBoundingBox();
}