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
	GameEngine::fillBackGround(1, 1, 1);
	//GameEngine::drawRect(-1000, -1000, 2000, 2000, 1, color, sb);
}

float Renderer::getDist(float _x1, float _y1, float _x2, float _y2)
{
	return sqrt((_x1 - _x2)*(_x1 - _x2) + (_y1 - _y2)*(_y1 - _y2));
}

glm::vec3 Renderer::convertVertex(glm::vec3 _v)
{
	/*float dist = getDist(_v.x, _v.y, viewPort.x, viewPort.y);
	float temp = dist *(-1 / ((_v.z / FOV + 1)*(_v.z / FOV + 1)) + 1);
	if (_v.z < -FOV) {
		//temp = dist *(-1 / (((-FOV + 0.1) / (FOV + 0.1) + 1)*(-FOV / FOV + 1)) + 1);
	}*/
	//temp = dist;
	//std::cout << "OO " << std::endl;
	glm::vec3 tempv;/*
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
	}*/
	tempv.y = (_v.y*FOV) / _v.z;
	tempv.x = (_v.x*FOV) / _v.z;
	if (_v.z < 0) {
		tempv.y = _v.y *-_v.z;
		tempv.x = _v.x *-_v.z;
	}
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
	
	//0 1 2
	if (box.vertices[0].z > 0 || box.vertices[1].z > 0 || box.vertices[2].z > 0) addNewFace(box.vertices[0], box.vertices[1], box.vertices[2]);
	//2 0 3
	if (box.vertices[2].z > 0 || box.vertices[0].z > 0 || box.vertices[3].z > 0) addNewFace(box.vertices[2], box.vertices[0], box.vertices[3]);
	//4 5 6
	if (box.vertices[4].z > 0 || box.vertices[5].z > 0 || box.vertices[6].z > 0) addNewFace(box.vertices[4], box.vertices[5], box.vertices[6]);
	//6 4 7
	if (box.vertices[6].z > 0 || box.vertices[4].z > 0 || box.vertices[7].z > 0) addNewFace(box.vertices[6], box.vertices[4], box.vertices[7]);
	//0 3 7
	if (box.vertices[0].z > 0 || box.vertices[3].z > 0 || box.vertices[7].z > 0) addNewFace(box.vertices[0], box.vertices[3], box.vertices[7]);
	//7 0 4
	if (box.vertices[7].z > 0 || box.vertices[0].z > 0 || box.vertices[4].z > 0) addNewFace(box.vertices[7], box.vertices[0], box.vertices[4]);
	//0 1 5
	if (box.vertices[0].z > 0 || box.vertices[1].z > 0 || box.vertices[5].z > 0) addNewFace(box.vertices[0], box.vertices[1], box.vertices[5]);
	//5 0 4
	if (box.vertices[5].z > 0 || box.vertices[0].z > 0 || box.vertices[4].z > 0) addNewFace(box.vertices[5], box.vertices[0], box.vertices[4]);
	//1 2 6
	if (box.vertices[1].z > 0 || box.vertices[2].z > 0 || box.vertices[6].z > 0) addNewFace(box.vertices[1], box.vertices[2], box.vertices[6]);
	//6 1 4
	if (box.vertices[6].z > 0 || box.vertices[1].z > 0 || box.vertices[4].z > 0) addNewFace(box.vertices[6], box.vertices[1], box.vertices[4]);
	//2 3 7
	if (box.vertices[2].z > 0 || box.vertices[3].z > 0 || box.vertices[7].z > 0) addNewFace(box.vertices[2], box.vertices[3], box.vertices[7]);
	//7 2 6
	if (box.vertices[7].z > 0 || box.vertices[2].z > 0 || box.vertices[6].z > 0) addNewFace(box.vertices[7], box.vertices[2], box.vertices[6]);
}

void Renderer::setViewPort(float _x, float _y)
{
	viewPort.x = _x;
	viewPort.y = _y;
}

void Renderer::setAllZToZero(Box * _box)
{
	for (int i = 0; i < 8; i++) {
		if (_box->vertices[i].z < 0) _box->vertices[i].z = 0.1;
	}
}

void Renderer::clipEdgeNear(glm::vec3* _p1, glm::vec3* _p2)//NOPE
{
	if (_p1->z < 0 || _p2->z < 0) {
		float temp = abs(_p1->z - _p2->z);
		if (_p1->z < _p2->z) {
			float temp1 = (-_p1->z + FOV) / temp;
			_p1->y = _p1->y + temp1*abs(_p1->y - _p2->y);
			_p1->x = _p1->x + temp1*abs(_p1->x - _p2->x);
		}
		else {
			float temp1 = (-_p2->z + FOV) / temp;
			_p2->y = _p2->y + temp1*abs(_p2->y - _p1->y);
			_p2->x = _p2->x + temp1*abs(_p2->x - _p1->x);
		}
	}
}

glm::vec3 Renderer::getClipEdgeNear(glm::vec3 _p1, glm::vec3 _p2)//YA
{
	if (_p1.z < 10 || _p2.z < 10) {
		float temp = get1DDist(_p1.z, _p2.z);
		if (_p1.z < _p2.z) {
			float temp1 = (-_p1.z+10) / (temp);
			_p1.y = _p1.y + temp1*get1DDist(_p1.y, _p2.y);
			_p1.x = _p1.x + temp1*get1DDist(_p1.x, _p2.x);
			_p1.z = 10;
			return _p1;
		}
		else {
			float temp1 = (-_p2.z+10) / (temp);
			_p2.y = _p2.y + temp1*get1DDist(_p2.y, _p1.y);
			_p2.x = _p2.x + temp1*get1DDist(_p2.x, _p1.x);
			_p2.z = 10;
			return _p2;
		}
	}
}

void Renderer::addNewFace(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3)
{
	Faces.push_back(Face(_p1, _p2, _p3, sqrt(pow((_p1.x + _p2.x + _p3.x) / 3, 2) + pow((_p1.y + _p2.y + _p3.y) / 3, 2) + pow((_p1.z + _p2.z + _p3.z) / 3, 2))));
}

float Renderer::get1DDist(float _x, float _y)
{
	if (_x > _y) {
		return abs(_x - _y);
	}
	else if (_x < _y) {
		return abs(_y - _x);
	}
	else {
		return 0;
	}
}

void Renderer::clipAllFaces()
{
	for (int i = 0; i < Faces.size(); i++) {
		clipFaceNear(&Faces[i]);
	}
}

void Renderer::clipFaceNear(Face * _face)
{
	glm::vec3 temp;
	Face tempFace(_face->p1, _face->p2, _face->p3, _face->distFromCamera);
	Face newFace();
	if (_face->p1.z < 10 || _face->p2.z < 10 || _face->p3.z < 10) {
		if (_face->p1.z < 10 && _face->p2.z > 10 && _face->p3.z > 10) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p3);
			temp = getClipEdgeNear(tempFace.p1, _face->p2);
			//addNewFace(temp, _face->p1, _face->p2);
		}
		else if (_face->p2.z < 10 && _face->p1.z > 10 && _face->p3.z > 10) {
			_face->p2 = getClipEdgeNear(_face->p2, _face->p3);
			temp = getClipEdgeNear(tempFace.p2, _face->p1);
			//addNewFace(temp, _face->p2, _face->p1);
		}
		else if (_face->p3.z < 10 && _face->p1.z > 10 && _face->p2.z > 10) {
			_face->p3 = getClipEdgeNear(_face->p3, _face->p2);
			temp = getClipEdgeNear(tempFace.p3, _face->p1);
			//addNewFace(temp, _face->p3, _face->p1);
		}/*
		else if (_face->p3.z < 10 && _face->p2.z < 10 && _face->p1.z > 10) {
			_face->p3 = getClipEdgeNear(_face->p3, _face->p1);
			_face->p2 = getClipEdgeNear(_face->p2, _face->p1);
		}
		else if (_face->p1.z < 10 && _face->p2.z < 10 && _face->p3.z > 10) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p3);
			_face->p2 = getClipEdgeNear(_face->p2, _face->p3);
		}
		else if (_face->p3.z < 10 && _face->p1.z < 10 && _face->p2.z > 10) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p2);
			_face->p3 = getClipEdgeNear(_face->p3, _face->p2);
		}*/
	}
}

void Renderer::drawAllFaces()
{
	orderFaces();
	for (int i = 0; i < Faces.size(); i++) {
		clipFaceNear(&Faces[i]);
		float averageDepth = 100;// (Faces[i].p1.z + Faces[i].p2.z + Faces[i].p3.z) / 3;
		GameEngine::drawBasicTriangle(convertVertex(Faces[i].p1), convertVertex(Faces[i].p2), convertVertex(Faces[i].p3), averageDepth / 200, 0, 200 / averageDepth);
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

Face::Face(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, float _distFromCamera)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	distFromCamera = _distFromCamera;
}
