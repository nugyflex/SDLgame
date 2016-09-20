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
	_x -= (gridSize + gridSize * 10)/2;
	_y -=( gridSize + gridSize * 10)/2;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			GameEngine::Color color;
			if (grid[i][j].isWall)
			{
				color.r = 200;
				color.g = 200;
				color.b = 200;
				color.a = 255;
			}
			else
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
				color.a = 0;
				color.b += (255 - color.b)*(1 - float(grid[i][j].pressure) / 10);
				color.r += (255 - color.r)*(float(grid[i][j].pressure) / 10);
				if (grid[i][j].pressure > 10)
				{
					color.r = 255;
					color.b = 0;
				}
				if (grid[i][j].water)
				{
					color.r = 0;
					color.g = 0;
					color.b = 100;
					//color.b += (255 - color.b)*(1 - float(grid[i][j].waterPressure) / 10);
					//color.r += (255 - color.r)*(float(grid[i][j].waterPressure) / 10);
				}
			}
			GameEngine::drawRect(_x + i*10 + i, _y + j*10 + j, cellSize, cellSize, 1, color, sb);
		}
	}
}
void Grid::reset()
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = Cell();
			grid[i][j].x = i;
			grid[i][j].y = j;
			grid[i][j].isWall = false;
			grid[i][j].pressure = 0;
			grid[i][j].waterVelocity = 0;
		}
	}
}
void Grid::addWall(int _x, int _y)
{
	grid[_x][_y].isWall = true;
}
void Grid::removeWall(int _x, int _y)
{
	grid[_x][_y].isWall = false;
}
bool cmd(const Cell* c1, const Cell* c2)
{
	return c1->pressure < c2->pressure;
}
void Grid::runGasSimulation()
{

	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			nextResult result = {false, false, false, false};
			int resultInt = 0;;
			//left
			if (x > 0 && !grid[x - 1][y].isWall && grid[x - 1][y].pressure < grid[x][y].pressure)
			{
				resultInt++;
				result.left = true;
			}
			//right
			if (x < gridSize - 1 && !grid[x + 1][y].isWall && grid[x + 1][y].pressure < grid[x][y].pressure)
			{
				resultInt++;
				result.right = true;
			}
			//up
			if (y < gridSize - 1 && !grid[x][y+1].isWall && grid[x][y + 1].pressure < grid[x][y].pressure)
			{
				resultInt++;
				result.up = true;
			}
			//down
			if (x > 0 && !grid[x][y - 1].isWall && grid[x][y - 1].pressure < grid[x][y].pressure)
			{
				resultInt++;
				result.down = true;
			}
			float amount = grid[x][y].pressure/2 / float(resultInt);
			if (result.left)
			{
				grid[x][y].pressure-=amount;
				grid[x - 1][y].pressure+= amount;
			}
			if (result.right)
			{
				grid[x][y].pressure-= amount;
				grid[x + 1][y].pressure+= amount;
			}
			if (result.up)
			{
				grid[x][y].pressure-= amount;
				grid[x][y + 1].pressure+= amount;
			}
			if (result.down)
			{
				grid[x][y].pressure-= amount;
				grid[x][y - 1].pressure+= amount;
			}
		}
	}

}
void Grid::runWaterSimulation()
{
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			grid[x][y].waterPressure = 0;
		}
	}
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			if (grid[x][y].water) {
				float exertpressure = 0;
				nextResult result = { false, false, false, false };
				//down
				if (x > 0 && !grid[x][y - 1].isWall && !grid[x][y - 1].water)
				{
					result.down = true;
				}

				//left
				if (x > 0 && !grid[x - 1][y].isWall && !grid[x - 1][y].water)
				{
					result.left = true;
				}
				//right
				if (x < gridSize - 1 && !grid[x + 1][y].isWall && !grid[x + 1][y].water)
				{
					result.right = true;
				}
				//up
				if (y < gridSize - 1 && !grid[x][y + 1].isWall && !grid[x][y + 1].water)
				{
					result.up = true;
				}
				
				if (result.down)
				{
					grid[x][y].water = false;
					grid[x][y - 1].water = true;
				}
				else if (result.left && result.right)
				{
					if (grid[x][y].waterVelocity == 0)
					{
						grid[x][y].waterVelocity = 1 - 2*((double)rand() / (RAND_MAX));
					}
					if (grid[x][y].waterVelocity < 0)
					{
						grid[x][y].water = false;
						grid[x - 1][y].water = true;
						grid[x - 1][y].waterVelocity = grid[x][y].waterVelocity;
					}
					else if (grid[x][y].waterVelocity > 0)
					{
						grid[x][y].water = false;
						grid[x + 1][y].water = true;
						grid[x + 1][y].waterVelocity = grid[x][y].waterVelocity;
					}
				}
				else if (result.left)
				{
					grid[x][y].water = false;
					grid[x - 1][y].water = true;
					grid[x - 1][y].waterVelocity = -1;
				}
				else if (result.right)
				{
					grid[x][y].water = false;
					grid[x + 1][y].water = true;
					grid[x + 1][y].waterVelocity = 1;
				}/*
				else if (grid[x][y].waterVelocity < 0)
				{
					grid[x][y].water = false;
					grid[x - 1][y].water = true;
				}
				else if (grid[x][y].waterVelocity > 0)
				{
					grid[x][y].water = false;
					grid[x + 1][y].water = true;
				}*/
			}
		}
	}

}
void Grid::setAsWall(int _x, int _y, bool isWall)
{
	grid[_x][_y].isWall = isWall;
}

void Grid::addPressure(int _x, int _y, float _amount)
{
	grid[_x][_y].pressure += _amount;
}
void Grid::reducePressure(int _x, int _y, float _amount)
{
	if (grid[_x][_y].pressure > _amount)
	{
		grid[_x][_y].pressure -= _amount;
	}
	else
	{
		grid[_x][_y].pressure = 0;
	}
}
void Grid::addWater(int _x, int _y)
{
	grid[_x][_y].water = true;
}