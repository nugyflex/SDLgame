#include "DrawText.h"



namespace GameEngine {
	DrawText::DrawText()
	{
	}


	DrawText::~DrawText()
	{
	}
	void DrawText::init(GameEngine::SpriteBatch* _sb) {
		texture = GameEngine::ResourceManager::getTexture("Textures/letters.png");
		sb = _sb;
	}

	glm::vec2 DrawText::getUVX(int _index) {
		int width;
		int uvx;
		if (_index < 12) {
			width = 3;
			uvx = _index * 4;
		}
		else if (_index == 12) {
			width = 5;
			uvx = _index * 4;
		}
		else if (_index == 13) {
			width = 4;
			uvx = 54;
		}
		else if (_index < 16) {
			width = 3;
			uvx = 59 + (_index - 14) * 4;
		}
		else if (_index == 16) {
			width = 4;
			uvx = 67;
		}
		else if (_index < 22) {
			width = 3;
			uvx = 72 + (_index - 17) * 4;
		}
		else if (_index == 22) {

			width = 5;
			uvx = 92;
		}
		else {
			width = 3;
			uvx = 97 + (_index - 23) * 4;
		}
		return glm::vec2(uvx, width);
	}
	void DrawText::draw(float _x, float _y, int _index) {
		glm::vec2 test = getUVX(_index);
		GameEngine::Color color;
		color.r = 10;
		color.g = 10;
		color.b = 10;
		color.a = 255;
		sb->draw(glm::vec4(-100.0f, 100.0f, test.y*3, 7*3), glm::vec4(test.x/149, 0, test.y / 149, 1), texture.id, 0.0f, color, -1);
	}
	int DrawText::getIndexFromString(std::string _string) {

	}
}
