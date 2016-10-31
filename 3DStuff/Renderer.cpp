#include "Renderer.h"

Renderer::Renderer(GameEngine::SpriteBatch* _sb)
{
}

Renderer::~Renderer()
{
}

void Renderer::drawLine(float _x1, float _y1, float _x2, float _y2)
{
	//sb->drawLine()
}

void Renderer::setViewPort(float _x, float _y)
{
	viewport.x = _x;
	viewport.y = _y;
}
