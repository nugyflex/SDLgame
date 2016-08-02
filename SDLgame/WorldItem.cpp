#include "WorldItem.h"

WorldItem::WorldItem() {}
WorldItem::~WorldItem() {}
void WorldItem::init(float _x, float _y, float _w, float _h)
{
	setPosition(glm::vec2(_x, _y));
	setSize(glm::vec2(_w, _h));
	setVel(glm::vec2(0, 0));
}
glm::vec2 WorldItem::getPosition()
{
	return position;
}
glm::vec2 WorldItem::getVel()
{
	return vel;
}
glm::vec2 WorldItem::getSize()
{
	return size;
}
glm::vec4 WorldItem::getRect()
{
	return glm::vec4(position.x, position.y, size.x, size.y);
}
void WorldItem::setLightID(int _ID) {
	lightID = _ID;
}
void WorldItem::setSize(glm::vec2 _size) {
	size = _size;
}
void WorldItem::setVel(glm::vec2 _vel) {
	vel = _vel;
}
void WorldItem::addToVel(glm::vec2 _vel) {
	vel += _vel;
}
void WorldItem::setPosition(glm::vec2 _position) {
	position = _position;
}
void WorldItem::addToPosition(glm::vec2 _position) {
	position += _position;
}
int WorldItem::getLightID() {
	return	lightID;
}
void WorldItem::setLightOffset(glm::vec2 _offset) {
	lightOffset = _offset;
}
glm::vec2 WorldItem::getLightOffset() {
	return lightOffset;
}