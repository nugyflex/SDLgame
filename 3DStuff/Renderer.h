#pragma once
#include "Box.h"
#include <glm.hpp>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
struct Face {
	Face(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, glm::vec3 _p4, float _distFromCamera);
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
	glm::vec3 p4;
	float distFromCamera;
};
struct sort_face
{
	inline bool operator() (const Face& _face1, const Face& _face2)
	{
		return (_face1.distFromCamera > _face2.distFromCamera);
	}
};

class Renderer {
public:
	Renderer(GameEngine::SpriteBatch* _sb);
	~Renderer();
	void drawBackGround();
	float getDist(float _x1, float _y1, float _x2, float _y2);
	glm::vec3 convertVertex(glm::vec3 _v);
	void drawLine(float _x1, float _y1, float _x2, float _y2);
	void drawLine(glm::vec3 _v1, glm::vec3 _v2);
	void drawBox(Box* _box);
	void setViewPort(float _x, float _y);
	void drawAllFaces();
	void resetFaces();
	void orderFaces();
	float FOV = 20;
	float cameraPitch;
	float cameraYaw;
	float cameraRoll;
private:
	std::vector<Face> Faces;
	glm::vec3 viewPort = glm::vec3(0,0,0);
	GameEngine::SpriteBatch* sb;
};