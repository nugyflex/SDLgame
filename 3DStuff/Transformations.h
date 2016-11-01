#pragma once
#include <glm.hpp>
#include <glm\gtx\rotate_vector.hpp>
static class Transformations {
public:
	static glm::vec2 rotateVertex(glm::vec2 _center, glm::vec2 _vertex, float _angle);
	static glm::vec2 multiply22x21(glm::mat2x2 _m, glm::vec2 _v);
};