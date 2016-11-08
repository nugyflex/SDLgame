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
	updateVertices();
	position.x = _x + _width/2;
	position.y = _y + _height / 2;
	position.z = _z + _depth / 2;
}

Box::~Box()
{
}

void Box::updateVertices()
{
	//Bottom
	vertices[0].x = position.x;
	vertices[0].y = position.y;
	vertices[0].z = position.z;

	vertices[1].x = position.x;
	vertices[1].y = position.y;
	vertices[1].z = position.z + dimensions.z;
	vertices[2].x = position.x + dimensions.x;
	vertices[2].y = position.y;
	vertices[2].z = position.z + dimensions.z;
	vertices[3].x = position.x + dimensions.x;
	vertices[3].y = position.y;
	vertices[3].z = position.z;
	//Top
	vertices[4].x = position.x;
	vertices[4].y = position.y + dimensions.y;
	vertices[4].z = position.z;
	vertices[5].x = position.x;
	vertices[5].y = position.y + dimensions.y;
	vertices[5].z = position.z + dimensions.z;
	vertices[6].x = position.x + dimensions.x;
	vertices[6].y = position.y + dimensions.y;
	vertices[6].z = position.z + dimensions.z;
	vertices[7].x = position.x + dimensions.x;
	vertices[7].y = position.y + dimensions.y;
	vertices[7].z = position.z;

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
