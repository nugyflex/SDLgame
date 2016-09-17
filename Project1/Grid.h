#pragma once
#include "Cell.h"
#include <GameEngine/SpriteBatch.h>
#include "glm.hpp"

class Grid
{
public:
	Grid(GameEngine::SpriteBatch* _sb);
	~Grid();
	void draw(int _x, int _y);
	void runAI();
	void setAsWall(int _x, int _y, bool isWall);
	void setStart(int _x, int _y);
	bool setEnd(int _x, int _y);
private:
	int cellSize = 10;
	const int gridSize = 10;
	Cell grid[10][10];
	GameEngine::SpriteBatch* sb;
	glm::vec2 start;
	glm::vec2 end;
	std::vector<Cell*> searched;
	std::vector<Cell*> finished;
	std::vector<Cell*> unsearched;
	bool isEndFound;
};