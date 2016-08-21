
#include "GlowStick.h"

GlowStick::GlowStick() {}
GlowStick::~GlowStick() {}
void GlowStick::run() {
	boundingBox.yv -= 0.6;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if (boundingBox.onGround) {
		boundingBox.xv *= 0.9;
	}
	boundingBox.onGround = false;
}

void GlowStick::loadSpriteSheet()
{
	centerSpriteSheet = false;
	boundingBox.w = 12;
	boundingBox.h = 2;
	spriteSheet.init(sb, 6, 1, 2, 1, 1, 0, 0);
	spriteSheet.loadTexture("Textures/glowstick.png");
}

GameEngine::Light GlowStick::getLight() {
	GameEngine::Light light;
	light.radius = 35;
	light.flicker = false;
	lightOffset = glm::vec2(6,1);
	light.color = glm::vec3(0.35, 1, 0.6);
	return light;
}
