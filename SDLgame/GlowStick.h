#pragma once

#include "WorldItem.h"

class GlowStick : public WorldItem {
public:
	GlowStick();
	~GlowStick();
	void run();
	void loadSpriteSheet() override;
	GameEngine::Light getLight();
};