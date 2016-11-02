#include "Renderer.h"
#include <GameEngine\CollisionDetection.h>
#include <iostream>
Renderer::Renderer(GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
}

Renderer::~Renderer()
{
}

void Renderer::drawBackGround()
{
	GameEngine::Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	GameEngine::fillBackGround(0, 0, 0);
	//GameEngine::drawRect(-1000, -1000, 2000, 2000, 1, color, sb);
}

float Renderer::getDist(float _x1, float _y1, float _x2, float _y2)
{
	return sqrt((_x1 - _x2)*(_x1 - _x2) + (_y1 - _y2)*(_y1 - _y2));
}

glm::vec3 Renderer::convertVertex(glm::vec3 _v)
{
	float dist = getDist(_v.x, _v.y, viewPort.x, viewPort.y);
	float temp = dist *(-1 / ((_v.z / FOV + 1)*(_v.z / FOV + 1)) + 1);
	if (_v.z < -FOV) {
		//temp = dist *(-1 / (((-FOV + 0.1) / (FOV + 0.1) + 1)*(-FOV / FOV + 1)) + 1);
	}
	//temp = dist;
	//std::cout << "z: " << _v.z << std::endl;
	glm::vec3 tempv;
	float theta = atan(-(viewPort.y - _v.y) / (viewPort.x - _v.x));
	float offsety;
	float offsetx;
	if (viewPort.x > _v.x) {
		offsety = sin(theta) * -temp;
		offsetx = cos(theta) * temp;
	}
	else if (viewPort.x == _v.x) {
		offsety = sin(theta) * -temp;
		offsetx = cos(theta) * -temp;
	}
	else {
		offsety = sin(theta) * temp;
		offsetx = cos(theta) * -temp;
	}
	tempv.y = _v.y + offsety;
	tempv.x = _v.x + offsetx;
	return tempv;
}
void Renderer::drawLine(float _x1, float _y1, float _x2, float _y2)
{
	//sb->drawLine()
}

void Renderer::drawLine(glm::vec3 _v1, glm::vec3 _v2)
{
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	glm::vec2 temp1 = glm::vec2(convertVertex(_v1).x, convertVertex(_v1).y);
	glm::vec2 temp2 = glm::vec2(convertVertex(_v2).x, convertVertex(_v2).y);
	GameEngine::drawBasicLine(temp1, temp2, 1, 1, 1, 1);
	//sb->drawLine(glm::vec2(convertVertex(_v1).x, convertVertex(_v1).y), glm::vec2(convertVertex(_v2).x, convertVertex(_v2).y), 255, 255, 255, 255, 1);
}
void Renderer::drawBox(Box* _box)
{
	bool array[8];
	for (int i = 0; i < 8; i++) {
		if (_box->vertices[i].z < -500) {
			array[i] = false;
		}
		else
		{
			array[i] = true;
		}
	}
	//Bottom
	if (array[0] || array[1]) drawLine(_box->vertices[0], _box->vertices[1]);
	if (array[1] || array[2]) drawLine(_box->vertices[1], _box->vertices[2]);
	if (array[2] || array[3]) drawLine(_box->vertices[2], _box->vertices[3]);
	if (array[3] || array[0]) drawLine(_box->vertices[3], _box->vertices[0]);
	//Top
	if (array[4] || array[5]) drawLine(_box->vertices[4], _box->vertices[5]);
	if (array[5] || array[6]) drawLine(_box->vertices[5], _box->vertices[6]);
	if (array[6] || array[7]) drawLine(_box->vertices[6], _box->vertices[7]);
	if (array[7] || array[4]) drawLine(_box->vertices[7], _box->vertices[4]);
	//Joins
	if (array[0] || array[4]) drawLine(_box->vertices[0], _box->vertices[4]);
	if (array[1] || array[5]) drawLine(_box->vertices[1], _box->vertices[5]);
	if (array[2] || array[6]) drawLine(_box->vertices[2], _box->vertices[6]);
	if (array[3] || array[7]) drawLine(_box->vertices[3], _box->vertices[7]);
	/*
	//Bottom
	drawLine(_box->vertices[0], _box->vertices[1]);
	drawLine(_box->vertices[1], _box->vertices[2]);
	drawLine(_box->vertices[2], _box->vertices[3]);
	drawLine(_box->vertices[3], _box->vertices[0]);
	//Top
	drawLine(_box->vertices[4], _box->vertices[5]);
	drawLine(_box->vertices[5], _box->vertices[6]);
	drawLine(_box->vertices[6], _box->vertices[7]);
	drawLine(_box->vertices[7], _box->vertices[4]);
	//Joins
	drawLine(_box->vertices[0], _box->vertices[4]);
	drawLine(_box->vertices[1], _box->vertices[5]);
	drawLine(_box->vertices[2], _box->vertices[6]);
	drawLine(_box->vertices[3], _box->vertices[7]);
	*/
	GameEngine::Color color;
	color.r = 255;
	color.g = 0;
	color.b = 0;
	GameEngine::drawRect(convertVertex(_box->position).x-2, convertVertex(_box->position).y-2, 4, 4, 1, color, sb);
	color.r = 0;
	color.g = 255;
	GameEngine::drawRect(-2, -2, 4, 4, 1, color, sb);
}

void Renderer::setViewPort(float _x, float _y)
{
	viewPort.x = _x;
	viewPort.y = _y;
}
