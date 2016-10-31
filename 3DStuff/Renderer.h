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
	Vertex convertVertex(Vertex _v);
	void drawLine(float _x1, float _y1, float _x2, float _y2);
	void drawLine(Vertex _v1, Vertex _v2);
	void drawBox(Box* _box);
	void setViewPort(float _x, float _y);
	float FOV = 2000;
private:
	glm::vec2 viewPort;
	GameEngine::SpriteBatch* sb;
};