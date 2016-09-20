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
	void reset();
	int startx;
	int starty;
	int endx;
	int endy;
	float heuristic(int _x1, int _y1);
	void addWall(int _x, int _y);
	void removeWall(int _x, int _y);
private:
	int x;
	int y;
	bool isFinished;
	bool oldIsFinished;
	int cellSize = 10;
	const int gridSize = 50;
	Cell grid[50][50];
	GameEngine::SpriteBatch* sb;

	std::vector<Cell*> searched;
	std::vector<Cell*> finished;
	std::vector<Cell*> unsearched;
	bool isEndFound;
	bool oldIsEndFound;
	int progress;
};