#include "Grid.h"
#include <GameEngine/GameEngine.h>
#include <iostream>
#include <functional>
#include <algorithm>

Grid::Grid(GameEngine::SpriteBatch* _sb)
{
	sb = _sb;
	init();
	reset();
	Wall_Horizontal.init(sb, 20, 2, 2, 1, 1, 0, 0);
	Wall_Horizontal.loadTexture("textures/wallHorizontal1.png");
	Wall_Verticle.init(sb, 2, 20, 2, 1, 1, 0, 0);
	Wall_Verticle.loadTexture("textures/wallVerticle1.png");
}

Grid::~Grid()
{
}

void Grid::draw(int _x, int _y)
{
	_x -= (gridSize + gridSize * cellSize)/2;
	_y -=( gridSize + gridSize * cellSize)/2;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			GameEngine::Color color;
			color.r = 10;
			color.g = 220;
			color.b = 10;/*
			if (grid[i][j].direction == left)
			{
				color.r = 25;
				color.g = 0;
				color.b = 0;
			}
			else if (grid[i][j].direction == right)
			{
				color.r = 0;
				color.g = 25;
				color.b = 0;
			}
			else if (grid[i][j].direction == up)
			{
				color.r = 0;
				color.g = 0;
				color.b = 25;
			}
			else if (grid[i][j].direction == down)
			{
				color.r = 0;
				color.g = 25;
				color.b = 25;
			}*/
			if (grid[i][j].direction == finished1)
			{
				color.r = 10;
				color.g = 220;
				color.b = 10;
			}
			if (grid[i][j].isWall) {
				color.r = 40;
				color.g = 40;
				color.b = 40;
			}
			GameEngine::drawRect(_x + i*cellSize + i, _y + j*cellSize + j, cellSize, cellSize, 1, color, sb);
			color.r = 255;
			color.g = 255;
			color.b = 255;
			if (grid[i][j].walls.up) {
				GameEngine::drawRect(_x + i*cellSize + i, _y + j*cellSize + j + cellSize, cellSize, 1, 1, color, sb);
			}
			if (grid[i][j].walls.down) {
				GameEngine::drawRect(_x + i*cellSize + i, _y + j*cellSize + j-1, cellSize, 1, 1, color, sb);
			}
			if (grid[i][j].walls.left) {
				GameEngine::drawRect(_x + i*cellSize + i-1, _y + j*cellSize + j, 1, cellSize, 1, color, sb);
			}
			if (grid[i][j].walls.right) {
				GameEngine::drawRect(_x + i*cellSize + i + cellSize, _y + j*cellSize + j, 1, cellSize, 1, color, sb);
			}
			if (!fireGrid[i][j].isExtinguished()) {
				fireGrid[i][j].draw(_x + i*cellSize + i, _y + j*cellSize + j);
			}
		}
	}
}
void Grid::reset()
{
	setStart(startx, starty);
	setEnd(endx, endy);
	searched.push_back(&grid[int(startx)][int(starty)]);
	isEndFound = false;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j].isPath = false;
			grid[i][j].finished = false;
			grid[i][j].searched = false;
			grid[i][j].isNew = true;
			grid[i][j].score = 100000;
			grid[i][j].isEnd = false;
			grid[i][j].direction = finished1;
		}
	}
	setEnd(endx, endy);
	searched.clear();
	searched.push_back(&grid[int(startx)][int(starty)]);
	grid[int(startx)][int(starty)].isNew = false;
	grid[int(startx)][int(starty)].score = 0;
	isEndFound = false;
	x = endx;
	y = endy;
	isFinished = false;
	progress = 0;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			fireGrid[i][j].health = 0;
		}
	}
}
void Grid::softReset()
{
	searched.push_back(&grid[int(startx)][int(starty)]);
	isEndFound = false;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			grid[i][j].isPath = false;
			grid[i][j].finished = false;
			grid[i][j].searched = false;
			grid[i][j].isNew = true;
			grid[i][j].score = 100000;
		}
	}
	searched.clear();
	searched.push_back(&grid[int(startx)][int(starty)]);
	grid[int(startx)][int(starty)].isNew = false;
	grid[int(startx)][int(starty)].score = 0;
	isEndFound = false;
	x = endx;
	y = endy;
	isFinished = false;
	progress = 0;
}
void Grid::addWall(int _x, int _y)
{
	grid[_x][_y].isWall = true;
}
void Grid::addBorderWalls(int _x, int _y, Direction direction)
{
	switch (direction) {
	case up:
		grid[_x][_y].walls.up = true;
		break;

	case down:
		grid[_x][_y].walls.down = true;
		break;

	case left:
		grid[_x][_y].walls.left = true;
		break;

	case right:
		grid[_x][_y].walls.right = true;
		break;
	}
}
void Grid::removeWall(int _x, int _y)
{
	grid[_x][_y].isWall = false;
}
void Grid::setFire(int _x, int _y)
{
	fireGrid[_x][_y].health = 10;
}
void Grid::spreadFire()
{
	
	if (spreadTimer == 0) {
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (!fireGrid[i][j].isExtinguished()) {
					//LEFT
					if (i - 1 >= 0 && !grid[i - 1][j].isWall && !grid[i - 1][j].walls.right && !grid[i][j].walls.left && ((double)rand() / (RAND_MAX)) > 0.85)
					{
						fireGrid[i - 1][j].health = 10;
					}
					//RIGHT
					if (i + 1 < gridSize && !grid[i + 1][j].isWall && !grid[i + 1][j].walls.left && !grid[i][j].walls.right && ((double)rand() / (RAND_MAX)) > 0.85)
					{
						fireGrid[i + 1][j].health = 10;
					}
					//DOWN
					if (j - 1 >= 0 && !grid[i][j - 1].isWall && !grid[i][j - 1].walls.up && !grid[i][j].walls.down && ((double)rand() / (RAND_MAX)) > 0.85)
					{
						fireGrid[i][j - 1].health = 10;
					}
					//UP
					if (j + 1 < gridSize &&!grid[i][j + 1].isWall && !grid[i][j + 1].walls.right && !grid[i][j].walls.up && ((double)rand() / (RAND_MAX)) > 0.85)
					{
						fireGrid[i][j + 1].health = 10;
					}
				}
			}
		}
		spreadTimer = 300;
	}
	spreadTimer--;
}
glm::vec2 Grid::getGridPosition(int _x, int _y)
{
	return glm::vec2(floor(((cellSize* gridSize + gridSize) / 2 + _x) / (cellSize + 1)), floor(((cellSize * gridSize + gridSize) / 2 + _y) / (cellSize + 1)));
}
void Grid::init()
{
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
			grid[i][j].isWall = false;
			grid[i][j].score = 100000;
			grid[i][j].direction = up;
		}
	}
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			fireGrid[i][j] = Fire(sb, i, j);
			fireGrid[i][j].health = 0;
		}
	}
}
float Grid::heuristic(int _x1, int _y1)
{
	return abs(_x1 - endx) + abs(_y1 - endy);
	//return sqrt(pow(abs(_x1 - endx), 2) + pow(abs(_y1 - endy), 2));
	//return abs(_x1 - endx) + abs(_y1 - endy)+ sqrt(pow(abs(_x1 - endx), 2) + pow(abs(_y1 - endy), 2));
}
bool cmd(const Cell* c1, const Cell* c2)
{
	return c1->priority < c2->priority; 
	
}
Path Grid::getPath() {
	//reset();
	Path path;
	isFinished = false;
	path.init();
	//setup
	int cellsEvaluated = 0;
	//getting directions
	while (searched.size() > 0 && !isEndFound)
	{
		int i = 0;
		while (searched.size() > 0 && !isEndFound)
		{
			std::sort(searched.begin(), searched.end(), cmd);
			if (!searched[i]->finished && !searched[i]->isNew) {

				if (searched[i]->isEnd)
				{
					isEndFound = true;
					break;
				}
				searched[i]->finished = true;
				///////////////
				///////////////
				///////////////
				///////////////
				//LEFT
				if (searched[i]->x > 0 && !grid[int(searched[i]->x - 1)][int(searched[i]->y)].isWall && !grid[int(searched[i]->x - 1)][int(searched[i]->y)].walls.right && !searched[i]->walls.left)
				{
					if (grid[int(searched[i]->x - 1)][int(searched[i]->y)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x - 1)][int(searched[i]->y)]);
						}
						searched.push_back(&grid[int(searched[i]->x - 1)][int(searched[i]->y)]);
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched = true;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].direction = right;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].score = searched[i]->score + 1;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].priority = heuristic(searched[i]->x - 1, searched[i]->y) + grid[int(searched[i]->x - 1)][int(searched[i]->y)].score / 200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x - 1)][int(searched[i]->y)].score < searched[i]->score)
					{
						searched[i]->direction = left;
					}
				}
				//RIGHT
				if (searched[i]->x < gridSize - 1 && !grid[int(searched[i]->x + 1)][int(searched[i]->y)].isWall && !grid[int(searched[i]->x + 1)][int(searched[i]->y)].walls.left && !searched[i]->walls.right)
				{
					if (grid[int(searched[i]->x + 1)][int(searched[i]->y)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x + 1)][int(searched[i]->y)]);
						}
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched = true;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].direction = left;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].score = searched[i]->score + 1;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].priority = heuristic(searched[i]->x + 1, searched[i]->y) + grid[int(searched[i]->x + 1)][int(searched[i]->y)].score / 200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x + 1)][int(searched[i]->y)].score < searched[i]->score)
					{
						searched[i]->direction = right;
					}
				}
				//DOWN
				if (searched[i]->y > 0 && !grid[int(searched[i]->x)][int(searched[i]->y - 1)].isWall && !grid[int(searched[i]->x)][int(searched[i]->y - 1)].walls.up && !searched[i]->walls.down)
				{
					if (grid[int(searched[i]->x)][int(searched[i]->y - 1)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y - 1)]);
						}
						searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y - 1)]);
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched = true;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].direction = up;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].score = searched[i]->score + 1;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].priority = heuristic(searched[i]->x, searched[i]->y - 1) + grid[int(searched[i]->x)][int(searched[i]->y - 1)].score / 200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x)][int(searched[i]->y - 1)].score < searched[i]->score)
					{
						searched[i]->direction = down;
					}
				}
				//UP
				if (searched[i]->y < gridSize - 1 && !grid[int(searched[i]->x)][int(searched[i]->y + 1)].isWall && !grid[int(searched[i]->x)][int(searched[i]->y)+1].walls.down && !searched[i]->walls.up)
				{
					if (grid[int(searched[i]->x)][int(searched[i]->y + 1)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y + 1)]);
						}
						searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y + 1)]);
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched = true;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].direction = down;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].score = searched[i]->score + 1;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].priority = heuristic(searched[i]->x, searched[i]->y + 1) + grid[int(searched[i]->x)][int(searched[i]->y + 1)].score / 200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x)][int(searched[i]->y + 1)].score < searched[i]->score)
					{
						searched[i]->direction = up;
					}
				}
				if (isEndFound)
				{
					break;
				}
				//searched[i]->searched = false;
				searched.erase(searched.begin() + i);
				//i--;
			}
			if (!isEndFound) {
				//std::cout <<  int(100*progress/pow(gridSize,2)) << "%  ";
				progress += cellsEvaluated;
				for (int j = 0; j < searched.size(); j++)
				{
					searched[j]->isNew = false;
					if (searched[j]->finished == true)
					{
						searched.erase(searched.begin() + j);
						j--;
					}
				}
			}
		}

	}
	draw(0,0);
	//getting path
	x = endx;
	y = endy;
	draw(0, 0);
	if (isEndFound)
	{
		int next = 0;
		while (!isFinished) {
			if (x == startx && y == starty)
			{
				isFinished = true;
			}
			else {
				int test2 = x;
				int test1 = y;
				
				std::cout << x << ",         " << y << "   |||||   " << endx << ",         " << endy << "   |||||   " << startx << ",         " << starty << "   |||||   " << grid[x][y].direction << "   |||||   " << std::endl;
				path.directionarray[next] = grid[x][y].direction;
				next++;

 				if (grid[x][y].direction == up && !grid[x][y].walls.up && !grid[x][y+1].walls.down)
				{
					y++;

				}
				else if (grid[x][y].direction == right && !grid[x][y].walls.right && !grid[x+1][y].walls.left)
				{ 
					x++;
				}
				else if (grid[x][y].direction == down && !grid[x][y].walls.down && !grid[x][y - 1].walls.up)
				{
					y--;
				}
				else if (grid[x][y].direction == left && !grid[x][y].walls.left && !grid[x-1][y].walls.right)
				{
					x--;
				}

			}
		}
			for (int i = 0; i < gridSize; i++)
			{
				for (int j = 0; j < gridSize; j++)
				{
					grid[i][j].finished = false;
					grid[i][j].searched = false;
				}
			}
		
	}
	if (isEndFound && !isFinished && !oldIsEndFound)
	{
		//std::cout << std::endl << "SCORE AND DIRECTION EVALUATION COMPLETE" << std::endl;
		//std::cout << "BEGINNING PATH FINDING..." << std::endl;
	}
	if (isFinished && !oldIsFinished)
	{
		//std::cout << "PATH-FINDING COMPLETE" << std::endl;
	}
	oldIsFinished = isFinished;
	oldIsEndFound = isEndFound;
	//reset();
	std::cout << "=======================================================" << std::endl;
	return path;
}
void Grid::runAI()
{
	//set up
	int cellsEvaluated = 0;

	//setting directions
	int steps = 0;
	while (searched.size() > 0 && !isEndFound && steps < 10)
	{
		int i = 0;
		while (searched.size() > 0 && steps < 10)
		{
			steps++;
			std::sort(searched.begin(), searched.end(), cmd);
			if (!searched[i]->finished && !searched[i]->isNew) {
				if (searched[i]->isEnd)
				{
					isEndFound = true;
					break;
				}
				searched[i]->finished = true;
				///////////////
				///////////////
				///////////////
				///////////////
				if (searched[i]->x > 0 && !grid[int(searched[i]->x - 1)][int(searched[i]->y)].isWall)
				{
					if (grid[int(searched[i]->x - 1)][int(searched[i]->y)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x - 1)][int(searched[i]->y)]);
						}
						searched.push_back(&grid[int(searched[i]->x - 1)][int(searched[i]->y)]);
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].searched = true;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].direction = right;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].score = searched[i]->score + 1;
						grid[int(searched[i]->x - 1)][int(searched[i]->y)].priority = heuristic(searched[i]->x - 1, searched[i]->y) + grid[int(searched[i]->x - 1)][int(searched[i]->y)].score/200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x - 1)][int(searched[i]->y)].score < searched[i]->score)
					{
						searched[i]->direction = left;
					}
				}
				if (searched[i]->x < gridSize - 1 && !grid[int(searched[i]->x + 1)][int(searched[i]->y)].isWall)
				{
					if (grid[int(searched[i]->x + 1)][int(searched[i]->y)].score > searched[i]->score + 1){
						if (!grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x + 1)][int(searched[i]->y)]);
						}
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].searched = true;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].direction = left;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].score = searched[i]->score + 1;
						grid[int(searched[i]->x + 1)][int(searched[i]->y)].priority = heuristic(searched[i]->x + 1, searched[i]->y) + grid[int(searched[i]->x + 1)][int(searched[i]->y)].score/200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x + 1)][int(searched[i]->y)].score < searched[i]->score)
					{
						searched[i]->direction = right;
					}
				}
				if (searched[i]->y > 0  &&  !grid[int(searched[i]->x)][int(searched[i]->y-1)].isWall)
				{
					if (grid[int(searched[i]->x)][int(searched[i]->y - 1)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y + 1)]);
						}
						searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y - 1)]);
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched = true;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].direction = up;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].score = searched[i]->score + 1;
						grid[int(searched[i]->x)][int(searched[i]->y - 1)].priority = heuristic(searched[i]->x, searched[i]->y - 1) + grid[int(searched[i]->x)][int(searched[i]->y - 1)].score/200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x)][int(searched[i]->y - 1)].score < searched[i]->score)
					{
						searched[i]->direction = down;
					}
				}
				if (searched[i]->y < gridSize - 1  && !grid[int(searched[i]->x)][int(searched[i]->y+1)].isWall)
				{
					if (grid[int(searched[i]->x)][int(searched[i]->y + 1)].score > searched[i]->score + 1) {
						if (!grid[int(searched[i]->x)][int(searched[i]->y - 1)].searched)
						{
							searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y - 1)]);
						}
						searched.push_back(&grid[int(searched[i]->x)][int(searched[i]->y + 1)]);
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].searched = true;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].direction = down;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].score = searched[i]->score + 1;
						grid[int(searched[i]->x)][int(searched[i]->y + 1)].priority = heuristic(searched[i]->x, searched[i]->y + 1) + grid[int(searched[i]->x)][int(searched[i]->y + 1)].score/200;
						cellsEvaluated++;
					}
					else if (grid[int(searched[i]->x)][int(searched[i]->y + 1)].score < searched[i]->score)
					{
						searched[i]->direction = up;
					}
				}
				if (isEndFound)
				{
					break;
				}
				//searched[i]->searched = false;
				searched.erase(searched.begin() + i);
				//i--;
			}
			if (!isEndFound) {
				//std::cout <<  int(100*progress/pow(gridSize,2)) << "%  ";
				progress += cellsEvaluated;
				for (int j = 0; j < searched.size(); j++)
				{
					searched[j]->isNew = false;
					if (searched[j]->finished == true)
					{
						searched.erase(searched.begin() + j);
						j--;
					}
				}
			}
		}

	}

	//getting path
	if (isEndFound)
	{
		while (!isFinished&& steps < 10)
		{
			steps++;
			if (x == startx && y == starty)
			{
				isFinished = true;
			}
			else{
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
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				grid[i][j].finished = false;
				grid[i][j].searched = false;
			}
		}
	}
	if (isEndFound && !isFinished && !oldIsEndFound)
	{
		//std::cout << std::endl << "SCORE AND DIRECTION EVALUATION COMPLETE" << std::endl;
		//std::cout << "BEGINNING PATH FINDING..." << std::endl;
	}
	if (isFinished && !oldIsFinished)
	{
		//std::cout << "PATH-FINDING COMPLETE" << std::endl;
	}
	oldIsFinished = isFinished;
	oldIsEndFound = isEndFound;
}

void Grid::setAsWall(int _x, int _y, bool isWall)
{
	grid[_x][_y].isWall = isWall;
}

void Grid::setStart(int _x, int _y)
{
	if (_x >= 0 && _x < gridSize - 1 && _y >= 0 && _y < gridSize - 1 && !grid[_x][_y].isWall) {
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (grid[i][j].isStart)
				{
					grid[i][j].isStart = false;
				}
			}
		}
		startx = _x;
		starty = _y;
		grid[_x][_y].isStart = true;
		grid[_x][_y].score = 0;
		searched.clear();
		searched.push_back(&grid[_x][_y]);
	}
}

bool Grid::setEnd(int _x, int _y)
{
	if (_x >= 0 && _x < gridSize - 1 && _y >= 0 && _y < gridSize - 1 && !grid[_x][_y].isWall) {
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (grid[i][j].isEnd)
				{
					grid[i][j].isEnd = false;
				}
			}
		}
		endx = _x;
		endy = _y;
		grid[_x][_y].isEnd = true;
		return true;
	}
}