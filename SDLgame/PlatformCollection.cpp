#include "PlatformCollection.h"
PlatformCollection::PlatformCollection() {}
PlatformCollection::~PlatformCollection() {}
void PlatformCollection::addPlatform(float _x, float _y, float _width, float _height) {
	platformVector.push_back(new Platform);
	platformVector[platformVector.size()-1]->init(_x, _y, _width, _height);
}
void PlatformCollection::drawPlatforms(GameEngine::SpriteBatch* sb) {
	for (int i = 0; i < platformVector.size(); i++)
	{
		platformVector[i]->draw(sb);
	}
}
BoundingBox* PlatformCollection::getBoundingBox(int _index) {
	return platformVector[_index]->getBoundingBox();
}