#pragma once
#include <glm.hpp>
#include "WorldItem.h"
class Flare : public WorldItem {
public:
	Flare();
	~Flare();
	void run();
	GameEngine::Light getLight();
};
class FlareParticle : public WorldItem {
public:
	FlareParticle();
	~FlareParticle();
	void run();
	GameEngine::Light getLight();
};