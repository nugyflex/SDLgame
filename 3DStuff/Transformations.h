#pragma once
#include <glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "Box.h"
static class Transformations {
public:
	static glm::vec2 rotateVertex(glm::vec2 _center, glm::vec2 _vertex, float _angle);
	static glm::vec3 translateVertex(glm::vec3 _vertex, glm::vec3 _translation);
	static glm::vec2 multiply22x21(glm::mat2x2 _m, glm::vec2 _v);
	static void translateBox(Box* _box, float _x, float _y, float _z);
	static void rotateBoxPitch(Box* _box, float _angle);
	static void rotateBoxYaw(Box* _box, float _angle);
	static void rotateBoxRoll(Box* _box, float _angle);
	static Box rotateBoxAroundCamera(Box* _box, glm::vec3 _camera, float _pitch, float _yaw, float _roll);
	static glm::vec3 rotateVertexPitch(glm::vec3 _position, glm::vec3 _vertex, float _angle);
	static glm::vec3 rotateVertexYaw(glm::vec3 _position, glm::vec3 _vertex, float _angle);
	static glm::vec3 rotateVertexRoll(glm::vec3 _position, glm::vec3 _vertex, float _angle);
};