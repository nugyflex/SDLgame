#pragma once
#include "GLTexture.h"
#include "SpriteBatch.h"
#include "ResourceManager.h"
#include <string>
namespace GameEngine {
	class DrawText
	{
	public:
		DrawText();
		~DrawText();
		void draw(float _x, float _y, int _index);
		void init(GameEngine::SpriteBatch* _sb);
	private:
		GameEngine::GLTexture texture;
		GameEngine::SpriteBatch* sb;
		glm::vec2 getUVX(int _index);
		int getIndexFromString(std::string _string);
	};
}