#include "Grid.h"
#include <GameEngine/GameEngine.h>
#include <iostream>
#include <functional>
#include <algorithm>

struct nextResult { bool left; bool right; bool up; bool down; };
Grid::Grid(GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
	reset();
}

Grid::~Grid()
{
}
void Grid::draw(int _x, int _y)
{
	_x -= (gridSize + gridSize * cellSize) / 2;
	_y -= (gridSize + gridSize * cellSize) / 2;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			GameEngine::Color color;
			color.r = 0;
			color.g = 0;
			color.b = 0;
			color.a = 255;
			color.b += (255 - color.b)*(1 - float(grid[i][j].value/2));
			color.r += (255 - color.r)*(float(grid[i][j].value/2));

			if (grid[i][j].value < waterLevel)
			{
				color.r = 255.0f * (grid[i][j].value / 120.0f)*0.75;
				color.g = 255.0f * (grid[i][j].value / 120.0f)*0.75;
				color.b = 255.0f * (grid[i][j].value / 120.0f)*1.8;
			}
			else if (grid[i][j].value < snowLine)
			{
				color.r = 255.0f * (grid[i][j].value / 120.0f)*0.4;
				color.g = 255.0f * (grid[i][j].value / 120.0f)*1.1;
				color.b = 255.0f * (grid[i][j].value / 120.0f)*0.7;
			}
			else
			{
				color.r = 255.0f * (grid[i][j].value / 120.0f)*1.2;
				color.g = 255.0f * (grid[i][j].value / 120.0f)*1.2;
				color.b = 255.0f * (grid[i][j].value / 120.0f)*1.4;
			}
			GameEngine::drawRect(_x + i * cellSize /*+ i*/, _y + j * cellSize /*+ j*/, cellSize, cellSize, 1, color, sb);
		}
	}
}
void Grid::reset()
{
	//((double)rand() / (RAND_MAX))
	//octaves++;
	bool test = true;
	//frequency+=0.01;
	noiseGen = new SimplexNoise(frequency, frequency*3, 0, 0);
	int offsetx = ((double)rand() / (RAND_MAX)) * 10000;
	int offsety = ((double)rand() / (RAND_MAX)) * 10000;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = Cell();
			grid[i][j].x = i;
			grid[i][j].y = j;

			double noise = 0;
			noise = floor(500*(noiseGen->fractal(1, i + offsetx, j + offsety)+0.05))*2;
			if (noise < 0)
			{
				noise = 0;
			}
			// between 0.05 and -0.05
			/*noise += (pn.noise(i, j, 0.12)) - floor(pn.noise(i, j, 0.12));
			noise += (pn.noise(i, j, 0.13)) - floor(pn.noise(i, j, 0.13));
			noise += (pn.noise(i, j, 0.14)) - floor(pn.noise(i, j, 0.14));
			noise += (pn.noise(i, j, 0.15)) - floor(pn.noise(i, j, 0.15));
			noise += (pn.noise(i, j, 0.16)) - floor(pn.noise(i, j, 0.16));
			noise += (pn.noise(i, j, 0.17)) - floor(pn.noise(i, j, 0.17));
			noise += (pn.noise(i, j, 0.18)) - floor(pn.noise(i, j, 0.18));
			noise += (pn.noise(i, j, 0.19)) - floor(pn.noise(i, j, 0.19));
			noise += (pn.noise(i, j, 0.20)) - floor(pn.noise(i, j, 0.20));
			noise += (pn.noise(i, j, 0.21)) - floor(pn.noise(i, j, 0.21));
			noise += (pn.noise(i, j, 0.22)) - floor(pn.noise(i, j, 0.22));
			noise += (pn.noise(i, j, 0.23)) - floor(pn.noise(i, j, 0.23));
			noise += (pn.noise(i, j, 0.24)) - floor(pn.noise(i, j, 0.24));
			noise += (pn.noise(i, j, 0.25)) - floor(pn.noise(i, j, 0.25));
			noise += (pn.noise(i, j, 0.26)) - floor(pn.noise(i, j, 0.26));
			noise += (pn.noise(i, j, 0.27)) - floor(pn.noise(i, j, 0.27));
			noise += (pn.noise(i, j, 0.28)) - floor(pn.noise(i, j, 0.28));
			noise += (pn.noise(i, j, 0.29)) - floor(pn.noise(i, j, 0.29));
			noise += (pn.noise(i, j, 0.30)) - floor(pn.noise(i, j, 0.30));
			noise += (pn.noise(i, j, 0.31)) - floor(pn.noise(i, j, 0.31));
			noise += (pn.noise(i, j, 0.32)) - floor(pn.noise(i, j, 0.32));
			noise += (pn.noise(i, j, 0.33)) - floor(pn.noise(i, j, 0.33));
			noise += (pn.noise(i, j, 0.34)) - floor(pn.noise(i, j, 0.34));
			noise += (pn.noise(i, j, 0.35)) - floor(pn.noise(i, j, 0.35));*/
			grid[i][j].value = noise;// noiseGenerator->noise(0.45, 0.8, 0.55);
		}
	}
}

float Grid::getValue(int _x, int _y)
{
	return grid[_x][_y].value;
}
