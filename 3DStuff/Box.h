#pragma once
#include <glm.hpp>
class Box {
public:
	Box(float _x, float _y, float _z, float _width, float _height, float _depth);
	~Box();
	void updateVertices();
	void init();
	glm::vec3 vertices[8];
	void setPosition(float _x, float _y, float _z);
	void addToPosition(float _x, float _y, float _z);
	float pitch = 0;
	float yaw = 0;
	float roll = 0;
	glm::vec3 position;
	glm::vec3 dimensions;
private:
};