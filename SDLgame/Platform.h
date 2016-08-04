#pragma once
#include <GameEngine\BoundingBox.h>
#include <GameEngine\SpriteBatch.h>
class Platform {
public:
	Platform();
	~Platform();
	void init(float _x, float _y, float _width, float _height);
	BoundingBox* getBoundingBox();
	void draw(GameEngine::SpriteBatch* sb);
private:
	BoundingBox boundingBox;
};