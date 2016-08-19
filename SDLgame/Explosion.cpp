#include "Explosion.h"

Explosion::Explosion() {}
Explosion::~Explosion() {}
void Explosion::run() {

}
GameEngine::Light Explosion::getLight() {
	GameEngine::Light light;
	light.radius = 200;
	light.flicker = false;
	light.flickerRange = glm::vec2(100, 200);
	light.color = glm::vec3(1, 0.5, 0.1);
	setLightOffset(0, 0);
	centerLight = true;
	return light;
}
void Explosion::loadSpriteSheet() {
	centerSpriteSheet = true;
	boundingBox.w = 60;
	boundingBox.h = 56;
	spriteSheet.init(sb, 30, 28, 2, 7, 4, 0, 0);
	spriteSheet.loadTexture("Textures/explosion.png");
}
ExplosionParticle::ExplosionParticle() {}
ExplosionParticle::~ExplosionParticle() {}
void ExplosionParticle::run() {
	boundingBox.yv -= 0.3;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if (boundingBox.onGround) {
		boundingBox.xv *= 0.9;
	}
	boundingBox.onGround = false;
}
GameEngine::Light ExplosionParticle::getLight() {
	GameEngine::Light light;
	light.radius = 0;
	light.flicker = true;
	light.flickerRange = glm::vec2(15, 20);
	light.color = glm::vec3(1, 0.4, 0.0);
	setLightOffset(3, 3);
	return light;
}
void ExplosionParticle::loadSpriteSheet() {
	spriteSheet.init(sb, 3, 3, 2, 9, 10, 0, 0);
	spriteSheet.loadTexture("Textures/explosionParticle.png");
}
FireParticle::FireParticle() {}
FireParticle::~FireParticle() {}
void FireParticle::run() {
	boundingBox.yv -= 0.4;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
	if (boundingBox.onGround) {
		boundingBox.xv *= 0.8;
	}
	boundingBox.onGround = false;
}
GameEngine::Light FireParticle::getLight() {
	GameEngine::Light light;
	light.radius = 0;
	light.flicker = true;
	light.flickerRange = glm::vec2(0, 50);
	light.color = glm::vec3(1, 0.5, 0.0);
	setLightOffset(3, 6);
	return light;
}
void FireParticle::loadSpriteSheet() {
	spriteSheet.init(sb, 3, 9, 2, 6, 4, 0, 0);
	spriteSheet.loadTexture("Textures/fireParticle.png");
}