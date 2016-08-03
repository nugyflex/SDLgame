#pragma once
#include <glm.hpp>
#include "WorldItem.h"
class GlowStick : public WorldItem {
public:
	GlowStick();
	~GlowStick();
	void run();
	GameEngine::Light getLight();
};