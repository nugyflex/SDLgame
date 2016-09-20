#pragma once
#include "Cell.h"
#include <GameEngine/SpriteBatch.h>
#include "glm.hpp"
#include "SimplexNoise.h"
class Grid
{
public:
	Grid(GameEngine::SpriteBatch* _sb);
	~Grid();
	void draw(int _x, int _y);
	void reset();
	int octaves = 1;
	float frequency = 0.01;
	int cellSize = 4;
	const int gridSize = 300;
	float getValue(int _x, int _y);
	int waterLevel = 30;
	int snowLine = 70;
private:
	SimplexNoise* noiseGen;
	Cell grid[300][300];
	GameEngine::SpriteBatch* sb;
};