#include "Renderer.h"
#include <GameEngine\CollisionDetection.h>
#include <iostream>
#include "Transformations.h"
#include <algorithm>
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
	//std::cout << "OO " << std::endl;
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
	tempv.z = _v.z;
	return tempv;
}
void Renderer::drawLine(float _x1, float _y1, float _x2, float _y2)
{
	//sb->drawLine()
}

void Renderer::drawLine(glm::vec3 _v1, glm::vec3 _v2)
{
	GameEngine::drawBasicLine(_v1, _v2, 1, 1, 1, 1);
}
void Renderer::drawBox(Box* _box)
{
	Box box = Transformations::rotateBoxAroundCamera(_box, viewPort, cameraPitch, cameraYaw, cameraRoll);
	bool array[8];
	glm::vec3 convertedVertices[8];

	for (int i = 0; i < 8; i++) {
		convertedVertices[i] = convertVertex(box.vertices[i]);
		if (box.vertices[i].z < 0) {
			array[i] = false;
		}
		else
		{
			array[i] = true;
		}
	}
	//std::cout << "NE" << std::endl;
	//Bottom
	/*
	if (array[0] || array[1]) drawLine(convertedVertices[0], convertedVertices[1]);
	if (array[1] || array[2]) drawLine(convertedVertices[1], convertedVertices[2]);
	if (array[2] || array[3]) drawLine(convertedVertices[2], convertedVertices[3]);
	if (array[3] || array[0]) drawLine(convertedVertices[3], convertedVertices[0]);
	//Top
	if (array[4] || array[5]) drawLine(convertedVertices[4], convertedVertices[5]);
	if (array[5] || array[6]) drawLine(convertedVertices[5], convertedVertices[6]);
	if (array[6] || array[7]) drawLine(convertedVertices[6], convertedVertices[7]);
	if (array[7] || array[4]) drawLine(convertedVertices[7], convertedVertices[4]);
	//Joins
	if (array[0] || array[4]) drawLine(convertedVertices[0], convertedVertices[4]);
	if (array[1] || array[5]) drawLine(convertedVertices[1], convertedVertices[5]);
	if (array[2] || array[6]) drawLine(convertedVertices[2], convertedVertices[6]);
	if (array[3] || array[7]) drawLine(convertedVertices[3], convertedVertices[7]);
	*/
	//FACES
	Faces.push_back(Face(convertedVertices[0], convertedVertices[1], convertedVertices[2], convertedVertices[3], sqrt(pow((box.vertices[0].x + box.vertices[1].x + box.vertices[2].x + box.vertices[3].x) / 4, 2) + pow((box.vertices[0].y + box.vertices[1].y + box.vertices[2].y + box.vertices[3].y) / 4, 2) + pow((box.vertices[0].z + box.vertices[1].z + box.vertices[2].z + box.vertices[3].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[4], convertedVertices[5], convertedVertices[6], convertedVertices[7], sqrt(pow((box.vertices[4].x + box.vertices[5].x + box.vertices[6].x + box.vertices[7].x) / 4, 2) + pow((box.vertices[4].y + box.vertices[5].y + box.vertices[6].y + box.vertices[7].y) / 4, 2) + pow((box.vertices[4].z + box.vertices[5].z + box.vertices[6].z + box.vertices[7].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[0], convertedVertices[3], convertedVertices[7], convertedVertices[4], sqrt(pow((box.vertices[0].x + box.vertices[3].x + box.vertices[7].x + box.vertices[4].x) / 4, 2) + pow((box.vertices[0].y + box.vertices[3].y + box.vertices[7].y + box.vertices[4].y) / 4, 2) + pow((box.vertices[0].z + box.vertices[3].z + box.vertices[7].z + box.vertices[4].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[0], convertedVertices[1], convertedVertices[5], convertedVertices[4], sqrt(pow((box.vertices[0].x + box.vertices[1].x + box.vertices[5].x + box.vertices[4].x) / 4, 2) + pow((box.vertices[0].y + box.vertices[1].y + box.vertices[5].y + box.vertices[4].y) / 4, 2) + pow((box.vertices[0].z + box.vertices[1].z + box.vertices[5].z + box.vertices[4].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[1], convertedVertices[2], convertedVertices[6], convertedVertices[5], sqrt(pow((box.vertices[1].x + box.vertices[2].x + box.vertices[6].x + box.vertices[5].x) / 4, 2) + pow((box.vertices[1].y + box.vertices[2].y + box.vertices[6].y + box.vertices[5].y) / 4, 2) + pow((box.vertices[1].z + box.vertices[2].z + box.vertices[6].z + box.vertices[5].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[0], convertedVertices[3], convertedVertices[7], convertedVertices[4], sqrt(pow((box.vertices[0].x + box.vertices[3].x + box.vertices[7].x + box.vertices[4].x) / 4, 2) + pow((box.vertices[0].y + box.vertices[3].y + box.vertices[7].y + box.vertices[4].y) / 4, 2) + pow((box.vertices[0].z + box.vertices[3].z + box.vertices[7].z + box.vertices[4].z) / 4, 2))));
	Faces.push_back(Face(convertedVertices[2], convertedVertices[3], convertedVertices[7], convertedVertices[6], sqrt(pow((box.vertices[2].x + box.vertices[3].x + box.vertices[7].x + box.vertices[6].x) / 4, 2) + pow((box.vertices[2].y + box.vertices[3].y + box.vertices[7].y + box.vertices[6].y) / 4, 2) + pow((box.vertices[2].z + box.vertices[3].z + box.vertices[7].z + box.vertices[6].z) / 4, 2))));
}

void Renderer::setViewPort(float _x, float _y)
{
	viewPort.x = _x;
	viewPort.y = _y;
}

void Renderer::drawAllFaces()
{
	orderFaces();
	for (int i = 0; i < Faces.size(); i++) {
		float averageDepth = (Faces[i].p1.z + Faces[i].p2.z + Faces[i].p3.z + Faces[i].p4.z) / 4;
		GameEngine::drawBasicQuad(Faces[i].p1, Faces[i].p2, Faces[i].p3, Faces[i].p4, 1, averageDepth/400, averageDepth/400);
	}
}

void Renderer::resetFaces()
{
	Faces.clear();
}

void Renderer::orderFaces()
{
	std::sort(Faces.begin(), Faces.end(), sort_face());
}

Face::Face(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, glm::vec3 _p4, float _distFromCamera)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	p4 = _p4;
	distFromCamera = _distFromCamera;
}
