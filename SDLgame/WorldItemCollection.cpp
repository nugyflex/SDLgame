#include "WorldItemCollection.h"
WorldItemCollection::WorldItemCollection(){}
WorldItemCollection::~WorldItemCollection(){}
void WorldItemCollection::init(LightCollection* _LC) {
	LC = _LC;
}
void WorldItemCollection::addItem(WorldItemType _type, float _x, float _y, float _xv, float _yv) {
	int lightID = 0;
	GameEngine::Light tempLight;
	switch (_type)
	{
	case flare:
		worldItemVector.push_back(new Flare());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1, 700);
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->yv = _yv;
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->xv = _xv;
		worldItemVector[worldItemVector.size() - 1]->setType(flare);
		break;
	case flareParticle:
		worldItemVector.push_back(new FlareParticle());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1, 80);
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->yv = _yv;
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->xv = _xv;
		worldItemVector[worldItemVector.size() - 1]->setType(flareParticle);
		break;
	case glowStick:
		worldItemVector.push_back(new GlowStick());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1);
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->yv = _yv;
		worldItemVector[worldItemVector.size() - 1]->getBoundingBox()->xv = _xv;
		worldItemVector[worldItemVector.size() - 1]->setType(glowStick);
		break;
	case default:

		break;
	}

	worldItemVector[worldItemVector.size() - 1]->setPosition(_x, _y);
	worldItemVector[worldItemVector.size() - 1]->setLightID(lightID);
}
void WorldItemCollection::addItem(WorldItemType _type, float _x, float _y) {
	int lightID = 0;
	GameEngine::Light tempLight;
	switch (_type)
	{ 
	case flare:
		worldItemVector.push_back(new Flare());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1, 700);
		worldItemVector[worldItemVector.size() - 1]->setType(flare);
		break;
	case flareParticle:
		worldItemVector.push_back(new FlareParticle());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1, 80);
		worldItemVector[worldItemVector.size() - 1]->setType(flareParticle);
		break;
	case glowStick:
		worldItemVector.push_back(new GlowStick());
		tempLight = worldItemVector[worldItemVector.size() - 1]->getLight();
		lightID = LC->addLight(tempLight);
		worldItemVector[worldItemVector.size() - 1]->init(0, 0, 1, 1);
		worldItemVector[worldItemVector.size() - 1]->setType(glowStick);
		break;
	case default:
		
		break;
	}
	
	worldItemVector[worldItemVector.size() - 1]->setPosition(_x, _y);
	worldItemVector[worldItemVector.size() - 1]->setLightID(lightID);
}
void WorldItemCollection::runItems() {
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		worldItemVector[i]->run();
		worldItemVector[i]->runTimer();
		if (worldItemVector[i]->getType() == flare && ((double)rand() / (RAND_MAX)) > 0.85) {
			addItem(flareParticle, worldItemVector[i]->getBoundingBox()->x, worldItemVector[i]->getBoundingBox()->y, ((double)rand() / (RAND_MAX)) * 6 - 3, ((double)rand() / (RAND_MAX)) * 16);
		}
		if (worldItemVector[i]->getTimer() <= 0 && worldItemVector[i]->despawns)
		{
			remove(i);
		}
	}
}
void WorldItemCollection::linkToLights()
{
	for (int i = 0; i < worldItemVector.size(); i++)
	{
		if (worldItemVector[i]->getLightID() != -1) {
			glm::vec2 temppos = worldItemVector[i]->getLightOffset() + glm::vec2(worldItemVector[i]->getBoundingBox()->x, worldItemVector[i]->getBoundingBox()->y);
			LC->changePosition(worldItemVector[i]->getLightID(), temppos.x, temppos.y);
		}
	}
}
BoundingBox* WorldItemCollection::getBoundingBox(int _index) {
	return worldItemVector[_index]->getBoundingBox();
}
void WorldItemCollection::remove(int _index) {
	if (worldItemVector[_index]->getLightID() != -1) {
		LC->removeLight(worldItemVector[_index]->getLightID());
	}
	worldItemVector.erase(worldItemVector.begin() + _index);
}