#include "Box.h"
Box::Box(float _x, float _y, float _z, float _width, float _height, float _depth) {
	x = _x;
	y = _y;
	z = _z;
	width = _width;
	height = _height;
	depth = _depth;
}

Box::~Box()
{
}

void Box::updateVertices()
{
	//Bottom
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = z;
	vertices[1].x = x;
	vertices[1].y = y;
	vertices[1].z = z + depth;
	vertices[2].x = x + width;
	vertices[2].y = y;
	vertices[2].z = z + depth;
	vertices[3].x = x + width;
	vertices[3].y = y;
	vertices[3].z = z;
	//Top
	vertices[4].x = x;
	vertices[4].y = y + height;
	vertices[4].z = z;
	vertices[5].x = x;
	vertices[5].y = y + height;
	vertices[5].z = z + depth;
	vertices[6].x = x + width;
	vertices[6].y = y + height;
	vertices[6].z = z + depth;
	vertices[7].x = x + width;
	vertices[7].y = y + height;
	vertices[7].z = z;
}

void Box::init()
{
	updateVertices();
}
