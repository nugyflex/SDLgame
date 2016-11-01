#include "Box.h"
#include <iostream>
#include "Transformations.h"
Box::Box(float _x, float _y, float _z, float _width, float _height, float _depth) {
	position.x = _x;
	position.y = _y;
	position.z = _z;
	dimensions.x = _width;
	dimensions.y = _height;
	dimensions.z = _depth;
}

Box::~Box()
{
}

void Box::updateVertices()
{
	std::cout << "1: " << position.x << std::endl;
	//Bottom
	vertices[0].x = position.x - dimensions.x / 2;
	vertices[0].y = position.y - dimensions.y / 2;
	vertices[0].z = position.z - dimensions.y / 2;

	vertices[1].x = position.x - dimensions.x / 2;
	vertices[1].y = position.y - dimensions.y / 2;
	vertices[1].z = position.z + dimensions.z / 2;
	vertices[2].x = position.x + dimensions.x / 2;
	vertices[2].y = position.y - dimensions.y / 2;;
	vertices[2].z = position.z + dimensions.z / 2;
	vertices[3].x = position.x + dimensions.x / 2;
	vertices[3].y = position.y - dimensions.y / 2;
	vertices[3].z = position.z - dimensions.z / 2;
	std::cout << "2: " << position.x << std::endl;
	//Top
	vertices[4].x = position.x - dimensions.x / 2;
	vertices[4].y = position.y + dimensions.y / 2;
	vertices[4].z = position.z - dimensions.z / 2;
	vertices[5].x = position.x - dimensions.x / 2;
	vertices[5].y = position.y + dimensions.y / 2;
	vertices[5].z = position.z + dimensions.z / 2;
	vertices[6].x = position.x + dimensions.x / 2;
	vertices[6].y = position.y + dimensions.y / 2;
	vertices[6].z = position.z + dimensions.z / 2;
	vertices[7].x = position.x + dimensions.x / 2;
	vertices[7].y = position.y + dimensions.y / 2;
	vertices[7].z = position.z - dimensions.z / 2;

	std::cout << "3: " << position.x << std::endl;
}

void Box::init()
{
	updateVertices();
}

void Box::setPosition(float _x, float _y, float _z)
{
	position.x = _x;
	position.y = _y;
	position.z = _z;
}

void Box::addToPosition(float _x, float _y, float _z)
{
	position.x += _x;
	position.y += _y;
	position.z += _z;
}
