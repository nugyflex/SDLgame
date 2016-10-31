#include "Renderer.h"
#include <GameEngine\CollisionDetection.h>
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
	GameEngine::drawRect(-1000, -1000, 2000, 2000, 1, color, sb);
}

float Renderer::getDist(float _x1, float _y1, float _x2, float _y2)
{
	return sqrt((_x1 - _x2)*(_x1 - _x2) + (_y1 - _y2)*(_y1 - _y2));
}

Vertex Renderer::convertVertex(Vertex _v)
{
	float dist = getDist(_v.x, _v.y, viewPort.x, viewPort.y);
	float temp = dist *(-1/((_v.z/FOV+1)*(_v.z/FOV+1)) + 1);
	/*if (log(_v.z) > 10) {
		temp = dist;
	}*/
	Vertex tempv;
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

void Renderer::drawLine(Vertex _v1, Vertex _v2)
{
	GameEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	sb->drawLine(glm::vec2(convertVertex(_v1).x, convertVertex(_v1).y), glm::vec2(convertVertex(_v2).x, convertVertex(_v2).y), 255, 255, 255, 255, 1);
}

void Renderer::drawBox(Box* _box)
{
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
}

void Renderer::setViewPort(float _x, float _y)
{
	viewPort.x = _x;
	viewPort.y = _y;
}
