#pragma once

#include "WorldItem.h"

class Explosion : public WorldItem {
public:
	Explosion();
	~Explosion();
	virtual void run() override;
	GameEngine::Light getLight() override;
	void loadSpriteSheet() override;
};
class ExplosionParticle : public WorldItem {
public:
	ExplosionParticle();
	~ExplosionParticle();
	void run() override;
	GameEngine::Light getLight() override;
	void loadSpriteSheet() override;
};
class FireParticle : public WorldItem {
public:
	FireParticle();
	~FireParticle();
	void run() override;
	GameEngine::Light getLight() override;
	void loadSpriteSheet() override;
};