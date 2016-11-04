#include "Transformations.h"

glm::vec2 Transformations::rotateVertex(glm::vec2 _center, glm::vec2 _vertex, float _angle)
{
	glm::vec2 offsetFromCenter = _vertex - _center;
	glm::mat2x2 m;
	m[0][0] = cos(_angle);
	m[0][1] = sin(_angle);
	m[1][0] = -sin(_angle);
	m[1][1] = cos(_angle);
	glm::vec2 result = multiply22x21(m, offsetFromCenter);
	return glm::vec2(result.x + _center.x, result.y + _center.y);
}

glm::vec3 Transformations::translateVertex(glm::vec3 _vertex, glm::vec3 _translation)
{
	return _vertex + _translation;
}

glm::vec2 Transformations::multiply22x21(glm::mat2x2 _m, glm::vec2 _v)
{
	return glm::vec2(_v.x*_m[0][0] + _v.y*_m[1][0], _v.x*_m[0][1] + _v.y*_m[1][1]);
}

void Transformations::translateBox(Box * _box, float _x, float _y, float _z)
{
	glm::vec3 temp = glm::vec3(_x, _y, _z);
	//bottom
	_box->vertices[0] = translateVertex(_box->vertices[0], temp);
	_box->vertices[1] = translateVertex(_box->vertices[1], temp);
	_box->vertices[2] = translateVertex(_box->vertices[2], temp);
	_box->vertices[3] = translateVertex(_box->vertices[3], temp);
	//top
	_box->vertices[4] = translateVertex(_box->vertices[4], temp);
	_box->vertices[5] = translateVertex(_box->vertices[5], temp);
	_box->vertices[6] = translateVertex(_box->vertices[6], temp);
	_box->vertices[7] = translateVertex(_box->vertices[7], temp);
	_box->position += temp;
}

void Transformations::rotateBoxPitch(Box * _box, float _angle)
{
	//bottom
	_box->vertices[0] = rotateVertexPitch(_box->position, _box->vertices[0], _angle);
	_box->vertices[1] = rotateVertexPitch(_box->position, _box->vertices[1], _angle);
	_box->vertices[2] = rotateVertexPitch(_box->position, _box->vertices[2], _angle);
	_box->vertices[3] = rotateVertexPitch(_box->position, _box->vertices[3], _angle);
	//top
	_box->vertices[4] = rotateVertexPitch(_box->position, _box->vertices[4], _angle);
	_box->vertices[5] = rotateVertexPitch(_box->position, _box->vertices[5], _angle);
	_box->vertices[6] = rotateVertexPitch(_box->position, _box->vertices[6], _angle);
	_box->vertices[7] = rotateVertexPitch(_box->position, _box->vertices[7], _angle);
}

void Transformations::rotateBoxYaw(Box * _box, float _angle)
{
	//bottom
	_box->vertices[0] = rotateVertexYaw(_box->position, _box->vertices[0], _angle);
	_box->vertices[1] = rotateVertexYaw(_box->position, _box->vertices[1], _angle);
	_box->vertices[2] = rotateVertexYaw(_box->position, _box->vertices[2], _angle);
	_box->vertices[3] = rotateVertexYaw(_box->position, _box->vertices[3], _angle);
	//top
	_box->vertices[4] = rotateVertexYaw(_box->position, _box->vertices[4], _angle);
	_box->vertices[5] = rotateVertexYaw(_box->position, _box->vertices[5], _angle);
	_box->vertices[6] = rotateVertexYaw(_box->position, _box->vertices[6], _angle);
	_box->vertices[7] = rotateVertexYaw(_box->position, _box->vertices[7], _angle);
}

void Transformations::rotateBoxRoll(Box * _box, float _angle)
{
	//bottom
	_box->vertices[0] = rotateVertexRoll(_box->position, _box->vertices[0], _angle);
	_box->vertices[1] = rotateVertexRoll(_box->position, _box->vertices[1], _angle);
	_box->vertices[2] = rotateVertexRoll(_box->position, _box->vertices[2], _angle);
	_box->vertices[3] = rotateVertexRoll(_box->position, _box->vertices[3], _angle);
	//top
	_box->vertices[4] = rotateVertexRoll(_box->position, _box->vertices[4], _angle);
	_box->vertices[5] = rotateVertexRoll(_box->position, _box->vertices[5], _angle);
	_box->vertices[6] = rotateVertexRoll(_box->position, _box->vertices[6], _angle);
	_box->vertices[7] = rotateVertexRoll(_box->position, _box->vertices[7], _angle);
}

Box Transformations::rotateBoxAroundCamera(Box* _box, glm::vec3 _camera, float _pitch, float _yaw, float _roll)
{
	Box box = Box(0,0,0, _box->dimensions.x,_box->dimensions.y,_box->dimensions.z);
	//PITCH
	//bottom
	box.vertices[0] = rotateVertexPitch(_camera, _box->vertices[0], _pitch);
	box.vertices[1] = rotateVertexPitch(_camera, _box->vertices[1], _pitch);
	box.vertices[2] = rotateVertexPitch(_camera, _box->vertices[2], _pitch);
	box.vertices[3] = rotateVertexPitch(_camera, _box->vertices[3], _pitch);
	//top
	box.vertices[4] = rotateVertexPitch(_camera, _box->vertices[4], _pitch);
	box.vertices[5] = rotateVertexPitch(_camera, _box->vertices[5], _pitch);
	box.vertices[6] = rotateVertexPitch(_camera, _box->vertices[6], _pitch);
	box.vertices[7] = rotateVertexPitch(_camera, _box->vertices[7], _pitch);
	//YAW
	box.vertices[0] = rotateVertexYaw(_camera, box.vertices[0], _yaw);
	box.vertices[1] = rotateVertexYaw(_camera, box.vertices[1], _yaw);
	box.vertices[2] = rotateVertexYaw(_camera, box.vertices[2], _yaw);
	box.vertices[3] = rotateVertexYaw(_camera, box.vertices[3], _yaw);
	//top
	box.vertices[4] = rotateVertexYaw(_camera, box.vertices[4], _yaw);
	box.vertices[5] = rotateVertexYaw(_camera, box.vertices[5], _yaw);
	box.vertices[6] = rotateVertexYaw(_camera, box.vertices[6], _yaw);
	box.vertices[7] = rotateVertexYaw(_camera, box.vertices[7], _yaw);
	//ROLL
	box.vertices[0] = rotateVertexRoll(_camera, box.vertices[0], _roll);
	box.vertices[1] = rotateVertexRoll(_camera, box.vertices[1], _roll);
	box.vertices[2] = rotateVertexRoll(_camera, box.vertices[2], _roll);
	box.vertices[3] = rotateVertexRoll(_camera, box.vertices[3], _roll);
	//top
	box.vertices[4] = rotateVertexRoll(_camera, box.vertices[4], _roll);
	box.vertices[5] = rotateVertexRoll(_camera, box.vertices[5], _roll);
	box.vertices[6] = rotateVertexRoll(_camera, box.vertices[6], _roll);
	box.vertices[7] = rotateVertexRoll(_camera, box.vertices[7], _roll);
	return box;
}

glm::vec3 Transformations::rotateVertexYaw(glm::vec3 _position, glm::vec3 _vertex, float _angle)
{
	glm::vec2 temp = rotateVertex(glm::vec2(_position.x, _position.y), glm::vec2(_vertex.x, _vertex.y), _angle);
	return glm::vec3(temp.x, temp.y, _vertex.z);
}

glm::vec3 Transformations::rotateVertexRoll(glm::vec3 _position, glm::vec3 _vertex, float _angle)
{
	glm::vec2 temp = rotateVertex(glm::vec2(_position.y, _position.z), glm::vec2(_vertex.y, _vertex.z), _angle);
	return glm::vec3(_vertex.x, temp.x, temp.y);
}

glm::vec3 Transformations::rotateVertexPitch(glm::vec3 _position, glm::vec3 _vertex, float _angle)
{
	glm::vec2 temp = rotateVertex(glm::vec2(_position.x, _position.z), glm::vec2(_vertex.x, _vertex.z), _angle);
	return glm::vec3(temp.x, _vertex.y, temp.y);
}
