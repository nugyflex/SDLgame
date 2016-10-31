#pragma once
#include "Vertex.h"
class Box {
public:
	Box(float _x, float _y, float _z, float _width, float _height, float _depth);
	~Box();
	void updateVertices();
	void init();
	Vertex vertices[7];
	float x;
	float y;
	float z;
	float width;
	float height;
	float depth;
private:

};