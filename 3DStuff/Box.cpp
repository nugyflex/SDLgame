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
	vertices[0].x = position.x;
	vertices[0].y = position.y;
	vertices[0].z = position.z;

	glm::vec2 test = Transformations::rotateVertex(glm::vec2(position.x + dimensions.x / 2, position.y + dimensions.y / 2), glm::vec2(position.x, position.x), 1);

	vertices[0].x = test.x;
	vertices[0].y = test.y;

	vertices[1].x = position.x;
	vertices[1].y = position.y;
	vertices[1].z = position.z + dimensions.z;
	vertices[2].x = position.x + dimensions.x;
	vertices[2].y = position.y;
	vertices[2].z = position.z + dimensions.z;
	vertices[3].x = position.x + dimensions.x;
	vertices[3].y = position.y;
	vertices[3].z = position.z;
	std::cout << "2: " << position.x << std::endl;
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
