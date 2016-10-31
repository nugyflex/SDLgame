#pragma once
#include "Box.h"
#include <glm.hpp>
#include <GameEngine\SpriteBatch.h>
class Renderer {
public:
	Renderer(GameEngine::SpriteBatch* _sb);
	~Renderer();
	void drawLine(float _x1, float _y1, float _x2, float _y2);
	void drawBox(Box _box);
	void setViewPort(float _x, float _y);
private:
	glm::vec2 viewport;
	float FOV;
	GameEngine::SpriteBatch* sb;
};