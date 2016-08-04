#include "Flare.h"

Flare::Flare() {}
Flare::~Flare() {}
void Flare::run() {
	boundingBox.yv -= 0.1;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}
GameEngine::Light Flare::getLight() {
	GameEngine::Light light;
	light.radius = 0;
	light.flicker = true;
	light.flickerRange = glm::vec2(50, 160);
	light.color = glm::vec3(1,0.15,0.15);
	return light;
}