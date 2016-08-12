#include "SpriteSheet.h"

namespace GameEngine {
	SpriteSheet::SpriteSheet()
	{
	}


	SpriteSheet::~SpriteSheet()
	{
	}

	void SpriteSheet::init(GameEngine::SpriteBatch * _sb, int _width, int _height, int _scale, int _numberOfFrames, int _frameChangeInterval, int _offSetX, int _offSetY)
	{
		sb = _sb;
		width = _width;
		height = _height;
		scale = _scale;
		numberOfFrames = _numberOfFrames;
		frameChangeInterval = _frameChangeInterval;
		offSetX = _offSetX;
		offSetY = _offSetY;
	}

	void SpriteSheet::loadTexture(std::string _path)
	{
		texture = GameEngine::ResourceManager::getTexture(_path);
	}

	void SpriteSheet::run()
	{
		frameChangeCounter++;
		if (frameChangeCounter == frameChangeInterval) {
			frameChangeCounter = 0;
			frame++;
			if (frame == numberOfFrames + 1) {
				frame = 0;
			}
		}
	}

	void SpriteSheet::draw(float _x, float _y)
	{
		GameEngine::Color color;
		color.r = 150;
		color.g = 150;
		color.b = 150;
		color.a = 255;
		sb->draw(glm::vec4(_x + offSetX*scale, _y + offSetY*scale, width*scale, height*scale), glm::vec4((1.0f / numberOfFrames)*frame, 0, (1.0f/numberOfFrames), 1), texture.id, 1, color, 1);
	}
	void SpriteSheet::reset()
	{
		frame = 0;
		frameChangeCounter = 0;
	}
}