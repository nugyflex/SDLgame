#include "GlowStick.h"

GlowStick::GlowStick() {}
GlowStick::~GlowStick() {}
void GlowStick::run() {
	boundingBox.yv -= 0.1;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
GameEngine::Light GlowStick::getLight() {
	GameEngine::Light light;
	light.radius = 0;
	light.flicker = true;
	light.flickerRange = glm::vec2(40, 45);
	light.color = glm::vec3(0.3, 1, 0.4);
	return light;
}