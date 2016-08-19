
#include <GameEngine\GameEngine.h>

#include "Platform.h"

Platform::Platform(){}
Platform::~Platform() {}
void Platform::init(float _x, float _y, float _width, float _height) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = _width;
	boundingBox.h = _height;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
	texture = GameEngine::ResourceManager::getTexture("Textures/basicPlatform8x1000.png");
}
BoundingBox* Platform::getBoundingBox() {
	return &boundingBox;
}
void Platform::draw(GameEngine::SpriteBatch* sb) {
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	//GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, 1, color, sb);
	sb->draw(glm::vec4(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h), glm::vec4(0, 0, boundingBox.w/(1000*2), 1), texture.id, 0.0f, color, 1);
}