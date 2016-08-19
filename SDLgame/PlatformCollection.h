#pragma once

#include <vector>
#include <string>

#include "Platform.h"

class PlatformCollection {
public:
	PlatformCollection();
	~PlatformCollection();
	void addPlatform(float _x, float _y, float _width, float _height);
	void drawPlatforms(GameEngine::SpriteBatch* sb);
	BoundingBox* getBoundingBox(int _index);
	int getVectorSize() { return platformVector.size(); }
private:
	std::vector<Platform*> platformVector;
};
