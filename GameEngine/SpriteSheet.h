#pragma once
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "ResourceManager.h"
namespace GameEngine {
	class SpriteSheet
	{
	public:
		SpriteSheet();
		~SpriteSheet();
		void init(GameEngine::SpriteBatch* _sb, int _width, int _height, int _scale, int _numberOfFrames, int _frameChangeInterval, int offSetX, int offSetY);
		void loadTexture(std::string _path);
		void run();
		void draw(float _x, float _y);
		void reset();
	private:
		int frame;
		int numberOfFrames;
		int frameChangeInterval;
		int frameChangeCounter;
		GameEngine::GLTexture texture;
		float width;
		float height;
		float scale;
		GameEngine::SpriteBatch* sb;
		int offSetX;
		int offSetY;
	};

}