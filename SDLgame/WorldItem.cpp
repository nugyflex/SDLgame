
#include "WorldItem.h"

WorldItem::WorldItem() {}
WorldItem::~WorldItem() {}
void WorldItem::init(float _x, float _y, float _w, float _h)
{
	setPosition(_x, _y);
	setSize(_w, _h);
	setVel(0, 0);
	despawns = false;
}
void WorldItem::init(float _x, float _y, float _w, float _h, int _timer)
{
	setPosition(_x, _y);
	setSize(_w, _h);
	setVel(0, 0);
	despawns = true;
	deSpawnTimer = _timer;
}
BoundingBox* WorldItem::getBoundingBox()
{
	return &boundingBox;
}
void WorldItem::setLightID(int _ID) {
	lightID = _ID;
}
void WorldItem::setSize(float _width, float _height) {
	boundingBox.w = _width;
	boundingBox.h = _height;
}
void WorldItem::setVel(float _xVel, float _yVel) {
	boundingBox.xv = _xVel;
	boundingBox.yv = _yVel;
}
void WorldItem::addToVel(float _xVel, float _yVel) {
	boundingBox.xv += _xVel;
	boundingBox.yv += _yVel;
}
void WorldItem::setPosition(float _x, float _y) {
	boundingBox.x = _x;
	boundingBox.y = _y;
}
void WorldItem::addToPosition(float _x, float _y) {
	boundingBox.x += _x;
	boundingBox.y += _y;
}
int WorldItem::getLightID() {
	return	lightID;
}
void WorldItem::setLightOffset(float _x, float _y) {
	lightOffset.x = _x;
	lightOffset.y = _y;
}
glm::vec2 WorldItem::getLightOffset() {
	return lightOffset;
}
void WorldItem::run() {

}
GameEngine::Light WorldItem::getLight() {
	GameEngine::Light x;
	return x;
}
void WorldItem::runTimer() {
	if (despawns){
		deSpawnTimer--;
	}
}
int WorldItem::getTimer() {
	return deSpawnTimer;
}
void WorldItem::drawSpriteSheet() {
	if (centerSpriteSheet) {
		spriteSheet.draw(boundingBox.x - boundingBox.w / 2, boundingBox.y - boundingBox.h / 2);
	}
	else {
		spriteSheet.draw(boundingBox.x + spriteSheetOffset.x, boundingBox.y + spriteSheetOffset.y);
	}
	spriteSheet.run();
}
void WorldItem::loadSpriteSheet() {

}
void WorldItem::draw() {

}