#pragma once

#include "WorldItem.h"

class Flare : public WorldItem {
public:
	Flare();
	~Flare();
	void run() override;
	void loadSpriteSheet() override;
	GameEngine::Light getLight() override;
};
class FlareParticle : public WorldItem {
public:
	FlareParticle();
	~FlareParticle();
	void run() override;
	GameEngine::Light getLight() override;
};
class DustCloudLanding : public WorldItem
{
public:
	DustCloudLanding();
	~DustCloudLanding();
	void loadSpriteSheet() override;
};