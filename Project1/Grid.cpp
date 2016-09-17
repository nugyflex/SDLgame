#include "Grid.h"
#include <GameEngine/GameEngine.h>
#include <iostream>
Grid::Grid(GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j] = Cell();
			grid[i][j].x = i;
			grid[i][j].y = j;
			grid[i][j].isNew = true;
			grid[i][j].isStart = false;
			grid[i][j].isEnd = false;
		}
	}
	setStart(1, 1);
	setEnd(9, 7);
	searched.push_back(&grid[int(start.x)][int(start.y)]);
	isEndFound = false;
}

Grid::~Grid()
{
}

void Grid::draw(int _x, int _y)
{
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
				color.r = 100;
				color.g = 100;
				color.b = 100;
				color.a = 255;
				if (grid[i][j].searched)
				{
					color.r = 255;
					color.g = 255;
					color.b = 255;
				}
				if (grid[i][j].finished)
				{
					color.r = 255;
					color.g = 50;
					color.b = 50;
				}
				if (grid[i][j].isPath)
				{
					color.r = 0;
					color.g = 255;
					color.b = 0;
				}
				if (grid[i][j].isStart)
				{
					color.r = 255;
					color.g = 255;
					color.b = 0;
					color.a = 255;
				}
				if (grid[i][j].isEnd)
				{
					color.r = 255;
					color.g = 255;
					color.b = 0;
					color.a = 255;
				}
			}
			GameEngine::drawRect(_x + i*10 + i, _y + j*10 + j, cellSize, cellSize, 1, color, sb);
		}
	}
}

void Grid::runAI()
{
	//set up
	int cellsEvaluated = 0;

	//setting directions

	if (searched.size() > 0 && !isEndFound)
	{
		for (int i = 0; i < searched.size(); i++)
		{
			if (!searched[i]->finished && !searched[i]->isNew) {
				searched[i]->finished = true;
				if (searched[i]->x > 0 && !grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched && !grid[int(searched[i]->x - 1)][int(searched[i]->y)].finished)
				{
					searched.push_back(&grid[int(searched[i]->x - 1)][int(searched[i]->y)]);
					grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched = true;
					grid[int(searched[i]->x - 1)][int(searched[i]->y)].direction = right;
					i++;
					cellsEvaluated++;
				}
				if (searched[i]->x < gridSize - 1 && !grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched && !grid[int(searched[i]->x + 1)][int(searched[i]->y)].finished)
				{
					searched.push_back(&grid[int(searched[i]->x + 1)][int(searched[i]->y)]);
					grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched = true;
					grid[int(searched[i]->x + 1)][int(searched[i]->y)].direction = left;
					i++;
					cellsEvaluated++;
				}
				if (searched[i]->y > 0 && !grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched && !grid[int(searched[i]->x)][int(searched[i]->y - 1)].finished)
				{
					searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y - 1)]);
					grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched = true;
					grid[int(searched[i]->x)][int(searched[i]->y - 1)].direction = up;
					i++;
					cellsEvaluated++;
				}
				if (searched[i]->y < gridSize - 1 && !grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched && !grid[int(searched[i]->x)][int(searched[i]->y + 1)].finished)
				{
					searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y + 1)]);
					grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched = true;
					grid[int(searched[i]->x)][int(searched[i]->y + 1)].direction = down;
					i++;
					cellsEvaluated++;
				}
				if (searched[i]->isEnd)
				{
					isEndFound = true;
					break;
				}
			}
		}
		if (!isEndFound) {
			for (int i = 0; i < searched.size(); i++)
			{
				searched[i]->isNew = false;
				if (searched[i]->finished == true)
				{
					searched[i]->searched = false;
					searched.erase(searched.begin() + i);
					i--;
				}
			}
		}
	}
	std::cout << "CELLS EVALUATED" << cellsEvaluated << std::endl;
	//getting path
	if (isEndFound)
	{
		int x = end.x;
		int y = end.y;
		while (x != start.x && y != start.y)
		{
			grid[x][y].isPath = true;
			if (grid[x][y].direction == up)
			{
				y++;
			}
			else if (grid[x][y].direction == right)
			{
				x++;
			}
			else if (grid[x][y].direction == down)
			{
				y--;
			}
			else if (grid[x][y].direction == left)
			{
				x--;
			}
		}
	}


}

void Grid::setAsWall(int _x, int _y, bool isWall)
{
	grid[_x][_y].isWall = isWall;
}

void Grid::setStart(int _x, int _y)
{
	start.x = _x;
	start.y = _y;
	grid[_x][_y].isStart = true;
}

bool Grid::setEnd(int _x, int _y)
{
	end.x = _x;
	end.y = _y;
	grid[_x][_y].isEnd = true;
	return true;
}
