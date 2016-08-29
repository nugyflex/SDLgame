
#include "Flare.h"
#include "Explosion.h"

Flare::Flare() {}
Flare::~Flare() {}
void Flare::run() {
	boundingBox.yv -= 0.2;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if (boundingBox.onGround) {
		boundingBox.xv *= 0.95;
	}
	boundingBox.onGround = false;
}

void Flare::loadSpriteSheet()
{
	centerSpriteSheet = false;
	boundingBox.w = 12;
	boundingBox.h = 2;
	spriteSheet.init(sb, 6, 1, 2, 1, 1, 0, 0);
	spriteSheet.loadTexture("Textures/flare.png");
}

GameEngine::Light Flare::getLight() {
	GameEngine::Light light;
	light.radius = 0;
	light.flicker = true;
	light.flickerRange = glm::vec2(50, 160);
	light.color = glm::vec3(1, 0.15, 0.15);
	return light;
}

FlareParticle::FlareParticle() {}
FlareParticle::~FlareParticle() {}
void FlareParticle::run() {
	boundingBox.yv -= 0.4;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if (boundingBox.onGround) {
		boundingBox.xv *= 0.8;
	}
	boundingBox.onGround = false;
}
GameEngine::Light FlareParticle::getLight() {
	GameEngine::Light light;
	light.radius = 15;
	light.flicker = false;
	light.color = glm::vec3(1, 0.25, 0.25);
	return light;
}
DustCloudLanding::DustCloudLanding(){}
DustCloudLanding::~DustCloudLanding(){}
void DustCloudLanding::loadSpriteSheet() {
	centerSpriteSheet = true;
	boundingBox.w = 10;
	boundingBox.h = 10;
	spriteSheet.init(sb, 24, 24, 2, 8, 3, 0, 0);
	spriteSheet.loadTexture("textures/dustAnimation2.png");
}