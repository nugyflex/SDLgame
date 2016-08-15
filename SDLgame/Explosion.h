#pragma once
#include <glm.hpp>
#include "WorldItem.h"
class Explosion : public WorldItem {
public:
	Explosion();
	~Explosion();
	void run();
	GameEngine::Light getLight();
	void loadSpriteSheet();
};
class FireParticle : public WorldItem {
public:
	FireParticle();
	~FireParticle();
	void run();
	GameEngine::Light getLight();
	void loadSpriteSheet();
};