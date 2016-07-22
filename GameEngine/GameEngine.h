#pragma once
#include <glm.hpp>
#include "Vertex.h"
#include "SpriteBatch.h"
namespace GameEngine {
	extern int init();
	extern void drawRect(int x, int y, int width, int height, Color color, SpriteBatch* spriteBatch);
	extern void drawLine(glm::vec2 point1, glm::vec2 point2, glm::mat4 cameraMatrix);
}
