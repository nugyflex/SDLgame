#include "GlowStick.h"

GlowStick::GlowStick() {}
GlowStick::~GlowStick() {}
void GlowStick::run() {
	boundingBox.yv -= 0.3;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
GameEngine::Light GlowStick::getLight() {
	GameEngine::Light light;
	light.radius = 35;
	light.flicker = false;
	light.color = glm::vec3(0.35, 1, 0.6);
	return light;
}