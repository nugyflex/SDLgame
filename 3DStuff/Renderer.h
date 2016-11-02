#pragma once
#include "Box.h"
#include <glm.hpp>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
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
	float FOV = 1;
private:
	glm::vec2 viewPort;
	GameEngine::SpriteBatch* sb;
};