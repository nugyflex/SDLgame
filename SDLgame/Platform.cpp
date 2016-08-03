#include "Platform.h"
#include <GameEngine\GameEngine.h>
Platform::Platform(){}
Platform::~Platform() {}
void Platform::init(float _x, float _y, float _width, float _height) {
	boundingBox.x = _x;
	boundingBox.y = _y;
	boundingBox.w = _width;
	boundingBox.h = _height;
	boundingBox.xv = 0;
	boundingBox.yv = 0;
}
BoundingBox* Platform::getBoundingBox() {
	return &boundingBox;
}
void Platform::draw(GameEngine::SpriteBatch* sb) {
	GameEngine::Color color;
	color.r = 1;
	color.g = 1;
	color.b = 1;
	color.a = 1;
	GameEngine::drawRect(boundingBox.x, boundingBox.y, boundingBox.w, boundingBox.h, color, sb);
}