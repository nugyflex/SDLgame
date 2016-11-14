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
	glm::vec3 tempv;
	float screenRatio = screenSize.y / screenSize.x;
	tempv.y = (_v.y*FOV) / _v.z;
	tempv.x = screenRatio*(_v.x*FOV) / _v.z;
	if (_v.z < 0) {
		tempv.y = _v.y *-_v.z;
		tempv.x = _v.x *-_v.z;
	}
	tempv.z = _v.z;
	return tempv;
}

void Renderer::drawLine(glm::vec3 _v1, glm::vec3 _v2)
{
	clipEdgeNear(&_v1, &_v2);
	GameEngine::drawBasicLine(convertVertex(_v1), convertVertex(_v2), 1.5, 0, 0, 0);
}
void Renderer::drawBox(Box* _box)
{
	Box* box = new Box();
	box->setVertices(_box->vertices);
	Transformations::translateBox(box, -cameraPosition.x, -cameraPosition.y, -cameraPosition.z);
	box = &Transformations::rotateBoxAroundCamera(box, glm::vec3(0,0,0), cameraPitch, cameraYaw, cameraRoll);
	bool array[8];
	glm::vec3 convertedVertices[8];

	for (int i = 0; i < 8; i++) {
		convertedVertices[i] = convertVertex(box->vertices[i]);
		if (box->vertices[i].z < 0) {
			array[i] = false;
		}
		else
		{
			array[i] = true;
		}
	}
	//0 1 2
	if (box->vertices[0].z > clippingPlaneZ || box->vertices[1].z > clippingPlaneZ || box->vertices[2].z > clippingPlaneZ) addNewFace(box->vertices[0], box->vertices[1], box->vertices[2]);
	//2 0 3
	if (box->vertices[2].z > clippingPlaneZ || box->vertices[0].z > clippingPlaneZ || box->vertices[3].z > clippingPlaneZ) addNewFace(box->vertices[2], box->vertices[0], box->vertices[3]);
	//4 5 6
	if (box->vertices[4].z > clippingPlaneZ || box->vertices[5].z > clippingPlaneZ || box->vertices[6].z > clippingPlaneZ) addNewFace(box->vertices[4], box->vertices[5], box->vertices[6]);
	//6 4 7
	if (box->vertices[6].z > clippingPlaneZ || box->vertices[4].z > clippingPlaneZ || box->vertices[7].z > clippingPlaneZ) addNewFace(box->vertices[6], box->vertices[4], box->vertices[7]);
	//0 3 7
	if (box->vertices[0].z > clippingPlaneZ || box->vertices[3].z > clippingPlaneZ || box->vertices[7].z > clippingPlaneZ) addNewFace(box->vertices[0], box->vertices[3], box->vertices[7]);
	//7 0 4
	if (box->vertices[7].z > clippingPlaneZ || box->vertices[0].z > clippingPlaneZ || box->vertices[4].z > clippingPlaneZ) addNewFace(box->vertices[7], box->vertices[0], box->vertices[4]);
	//0 1 5
	if (box->vertices[0].z > clippingPlaneZ || box->vertices[1].z > clippingPlaneZ || box->vertices[5].z > clippingPlaneZ) addNewFace(box->vertices[0], box->vertices[1], box->vertices[5]);
	//5 0 4
	if (box->vertices[5].z > clippingPlaneZ || box->vertices[0].z > clippingPlaneZ || box->vertices[4].z > clippingPlaneZ) addNewFace(box->vertices[5], box->vertices[0], box->vertices[4]);
	//1 2 6
	if (box->vertices[1].z > clippingPlaneZ || box->vertices[2].z > clippingPlaneZ || box->vertices[6].z > clippingPlaneZ) addNewFace(box->vertices[1], box->vertices[2], box->vertices[6]);
	//6 1 4 - > 6 1 5
	if (box->vertices[6].z > clippingPlaneZ || box->vertices[1].z > clippingPlaneZ || box->vertices[5].z > clippingPlaneZ) addNewFace(box->vertices[6], box->vertices[1], box->vertices[5]);
	//2 3 7
	if (box->vertices[2].z > clippingPlaneZ || box->vertices[3].z > clippingPlaneZ || box->vertices[7].z > clippingPlaneZ) addNewFace(box->vertices[2], box->vertices[3], box->vertices[7]);
	//7 2 6
	if (box->vertices[7].z > clippingPlaneZ || box->vertices[2].z > clippingPlaneZ || box->vertices[6].z > clippingPlaneZ) addNewFace(box->vertices[7], box->vertices[2], box->vertices[6]);
	//LINES
	if (box->vertices[0].z > clippingPlaneZ || box->vertices[1].z > clippingPlaneZ) drawLine(box->vertices[0], box->vertices[1]);
	if (box->vertices[1].z > clippingPlaneZ || box->vertices[2].z > clippingPlaneZ)drawLine(box->vertices[1], box->vertices[2]);
	if (box->vertices[2].z > clippingPlaneZ || box->vertices[3].z > clippingPlaneZ)drawLine(box->vertices[2], box->vertices[3]);
	if (box->vertices[3].z > clippingPlaneZ || box->vertices[0].z > clippingPlaneZ)drawLine(box->vertices[3], box->vertices[0]);
	if (box->vertices[4].z > clippingPlaneZ || box->vertices[5].z > clippingPlaneZ)drawLine(box->vertices[4], box->vertices[5]);
	if (box->vertices[5].z > clippingPlaneZ || box->vertices[6].z > clippingPlaneZ)drawLine(box->vertices[5], box->vertices[6]);
	if (box->vertices[6].z > clippingPlaneZ || box->vertices[7].z > clippingPlaneZ)drawLine(box->vertices[6], box->vertices[7]);
	if (box->vertices[7].z > clippingPlaneZ || box->vertices[4].z > clippingPlaneZ)drawLine(box->vertices[7], box->vertices[4]);
	if (box->vertices[0].z > clippingPlaneZ || box->vertices[4].z > clippingPlaneZ)drawLine(box->vertices[0], box->vertices[4]);
	if (box->vertices[1].z > clippingPlaneZ || box->vertices[5].z > clippingPlaneZ)drawLine(box->vertices[1], box->vertices[5]);
	if (box->vertices[2].z > clippingPlaneZ || box->vertices[6].z > clippingPlaneZ)drawLine(box->vertices[2], box->vertices[6]);
	if (box->vertices[3].z > clippingPlaneZ || box->vertices[7].z > clippingPlaneZ)drawLine(box->vertices[3], box->vertices[7]);
}

void Renderer::setCameraPosition(float _x, float _y)
{
	cameraPosition.x = _x;
	cameraPosition.y = _y;
}

void Renderer::addToCameraPosition(float _x, float _y, float _z)
{
	cameraPosition.x += _x;
	cameraPosition.y += _y;
	cameraPosition.z += _z;
}

void Renderer::setAllZToZero(Box * _box)
{
	for (int i = 0; i < 8; i++) {
		if (_box->vertices[i].z < 0) _box->vertices[i].z = 0.1;
	}
}

void Renderer::clipEdgeNear(glm::vec3* _p1, glm::vec3* _p2)//NOPE
{
	if (_p1->z < clippingPlaneZ || _p2->z < clippingPlaneZ) {
		float temp = get1DDist(_p1->z, _p2->z);
		if (_p1->z < _p2->z) {
			float temp1 = (-_p1->z + clippingPlaneZ) / (temp);
			_p1->y = _p1->y + temp1*(_p2->y - _p1->y);
			_p1->x = _p1->x + temp1*(_p2->x - _p1->x);
			_p1->z = clippingPlaneZ;
		}
		else {
			float temp1 = (-_p2->z + clippingPlaneZ) / (temp);
			_p2->y = _p2->y + temp1*(_p1->y - _p2->y);
			_p2->x = _p2->x + temp1*(_p1->x - _p2->x);
			_p2->z = clippingPlaneZ;
		}
	}
}

glm::vec3 Renderer::getClipEdgeNear(glm::vec3 _p1, glm::vec3 _p2)//YA
{
	if (_p1.z < clippingPlaneZ || _p2.z < clippingPlaneZ) {
		float temp = get1DDist(_p1.z, _p2.z);
		if (_p1.z < _p2.z) {
			float temp1 = (-_p1.z+clippingPlaneZ) / (temp);
			_p1.y = _p1.y + temp1*(_p2.y - _p1.y);
			_p1.x = _p1.x + temp1*(_p2.x - _p1.x);
			_p1.z = clippingPlaneZ;
			return _p1;
		}
		else {
			float temp1 = (-_p2.z+clippingPlaneZ) / (temp);
			_p2.y = _p2.y + temp1*(_p1.y - _p2.y);
			_p2.x = _p2.x + temp1*(_p1.x - _p2.x);
			_p2.z = clippingPlaneZ;
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

void Renderer::clipFaceNear(Face * _face)
{
	glm::vec3 temp;
	Face tempFace(_face->p1, _face->p2, _face->p3, _face->distFromCamera);
	Face newFace();
	if (_face->p1.z < clippingPlaneZ || _face->p2.z < clippingPlaneZ || _face->p3.z < clippingPlaneZ) {
		if (_face->p1.z < clippingPlaneZ && _face->p2.z > clippingPlaneZ && _face->p3.z > clippingPlaneZ) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p3);
			temp = getClipEdgeNear(tempFace.p1, _face->p2);
			addNewFace(temp, _face->p1, _face->p2);
		}
		else if (_face->p2.z < clippingPlaneZ && _face->p1.z > clippingPlaneZ && _face->p3.z > clippingPlaneZ) {
			_face->p2 = getClipEdgeNear(_face->p2, _face->p3);
			temp = getClipEdgeNear(tempFace.p2, _face->p1);
			addNewFace(temp, _face->p2, _face->p1);
		}
		else if (_face->p3.z < clippingPlaneZ && _face->p1.z > clippingPlaneZ && _face->p2.z > clippingPlaneZ) {
			_face->p3 = getClipEdgeNear(_face->p3, _face->p2);
			temp = getClipEdgeNear(tempFace.p3, _face->p1);
			addNewFace(temp, _face->p3, _face->p1);
		}
		else if (_face->p3.z < clippingPlaneZ && _face->p2.z < clippingPlaneZ && _face->p1.z > clippingPlaneZ) {
			_face->p3 = getClipEdgeNear(_face->p3, _face->p1);
			_face->p2 = getClipEdgeNear(_face->p2, _face->p1);
		}
		else if (_face->p1.z < clippingPlaneZ && _face->p2.z < clippingPlaneZ && _face->p3.z > clippingPlaneZ) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p3);
			_face->p2 = getClipEdgeNear(_face->p2, _face->p3);
		}
		else if (_face->p3.z < clippingPlaneZ && _face->p1.z < clippingPlaneZ && _face->p2.z > clippingPlaneZ) {
			_face->p1 = getClipEdgeNear(_face->p1, _face->p2);
			_face->p3 = getClipEdgeNear(_face->p3, _face->p2);
		}
	}
}

void Renderer::drawAllFaces()
{
	orderFaces();
	for (int i = 0; i < Faces.size(); i++) {
		clipFaceNear(&Faces[i]);
		float averageDepth = (Faces[i].p1.z + Faces[i].p2.z + Faces[i].p3.z) / 3;
		GameEngine::drawBasicTriangle(convertVertex(Faces[i].p1), convertVertex(Faces[i].p2), convertVertex(Faces[i].p3), 1, 1, 0.78);
	}
}

void Renderer::resetFaces()
{
	Faces.clear();
}

void Renderer::collisionDetection3D(Box* _box1, Box * _box2)
{
	//xy
	/*
	if (_box1->position.x < _box2->position.x + _box2->dimensions.x && _box1->position.x + _box1->dimensions.x > _box2->position.x && _box1->position.y < _box2->position.y + _box2->dimensions.y && _box1->position.y + _box1->dimensions.y > _box2->position.y) {
		if (_box1->velocity.z > _box2->position.z - _box1->position.z - _box1->dimensions.z) {
			_box1->position.z = _box2->position.z - _box1->dimensions.z;
		}
		if (-_box1->velocity.z > _box1->position.z - _box2->position.z - _box2->dimensions.z) {
			_box1->position.z = _box2->position.z + _box2->dimensions.z;
		}
	}*/
	//xz
	if (_box1->position.x < _box2->position.x + _box2->dimensions.x && _box1->position.x + _box1->dimensions.x > _box2->position.x && _box1->position.z < _box2->position.z + _box2->dimensions.z && _box1->position.z + _box1->dimensions.z > _box2->position.z) {
		if (_box1->position.y + _box1->dimensions.y <= _box2->position.y && _box1->velocity.y + _box1->dimensions.y + _box1->position.y >= _box2->position.y) {
			_box1->position.y = _box2->position.y - _box1->dimensions.y;
			_box1->velocity.y = 0;
		}
		if (-_box1->velocity.y > _box1->position.y - _box2->position.y - _box2->dimensions.y) {
			_box1->position.y = _box2->position.y + _box2->dimensions.y;
		}
	}
	//yz
	/*
	if (_box1->position.z < _box2->position.z + _box2->dimensions.z && _box1->position.z + _box1->dimensions.z > _box2->position.z && _box1->position.y < _box2->position.y + _box2->dimensions.y && _box1->position.y + _box1->dimensions.y > _box2->position.y) {
		if (_box1->velocity.x > _box2->position.x - _box1->position.x - _box1->dimensions.x) {
			_box1->position.x = _box2->position.x - _box1->dimensions.x;
		}
		if (-_box1->velocity.x > _box1->position.x - _box2->position.x - _box2->dimensions.x) {
			_box1->position.x = _box2->position.x + _box2->dimensions.x;
		}
	}*/
}

void Renderer::orderFaces()
{
	std::sort(Faces.begin(), Faces.end(), sort_face());
}

void Renderer::setScreenSize(float _x, float _y)
{
	screenSize.x = _x;
	screenSize.y = _y;
}

Face::Face(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, float _distFromCamera)
{
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	distFromCamera = _distFromCamera;
}