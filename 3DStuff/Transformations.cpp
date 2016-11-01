#include "Transformations.h"

glm::vec2 Transformations::rotateVertex(glm::vec2 _center, glm::vec2 _vertex, float _angle)
{
	glm::mat2x2 m;
	m[0][0] = cos(_angle);
	m[0][1] = sin(_angle);
	m[1][0] = -sin(_angle);
	m[1][1] = -cos(_angle);
	return multiply22x21(m, _vertex);
}

glm::vec2 Transformations::multiply22x21(glm::mat2x2 _m, glm::vec2 _v)
{
	return glm::vec2(_v.x*_m[0][0] + _v.x*_m[0][1], _v.y*_m[1][0] + _v.y*_m[1][1]);
}
