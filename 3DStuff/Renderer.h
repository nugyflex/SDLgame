#pragma once
#include "box.h"
#include <glm.hpp>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
struct Face {
	Face(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3, float _distFromCamera);
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
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
	void drawLine(glm::vec3 _v1, glm::vec3 _v2);
	void drawBox(Box* _box);
	void setCameraPosition(float _x, float _y);
	void addToCameraPosition(float _x, float _y, float _z);
	void setAllZToZero(Box* _box);
	void clipEdgeNear(glm::vec3* _p1, glm::vec3* _p2);
	glm::vec3 getClipEdgeNear(glm::vec3 _p1, glm::vec3 _p2);
	void addNewFace(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3);
	float get1DDist(float _x, float _y);
	void clipFaceNear(Face* _face);
	void drawAllFaces();
	void resetFaces();
	void collisionDetection3D(Box* _box1, Box* _box2);
	void orderFaces();
	void drawGrid();
	float FOV = 1;
	float cameraPitch;
	float cameraYaw;
	float cameraRoll;
	float clippingPlaneZ = 1;
	glm::vec2 screenSize;
	void setScreenSize(float _x, float _y);
	glm::vec3 cameraPosition = glm::vec3(0, 0, 0);
private:
	std::vector<Face> Faces;
	GameEngine::SpriteBatch* sb;
};