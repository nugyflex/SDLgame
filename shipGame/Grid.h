#pragma once
#include "Cell.h"
#include <GameEngine/SpriteBatch.h>
#include "glm.hpp"
#include "Path.h"
#include "fire.h"
enum Tile {corridorHorizontal, corridorVerticle};
class Grid
{
public:
	Grid(GameEngine::SpriteBatch* _sb);
	~Grid();
	void draw(int _x, int _y);
	void runAI();
	Path getPath();
	void setAsWall(int _x, int _y, bool isWall);
	void setStart(int _x, int _y);
	bool setEnd(int _x, int _y);
	void reset();
	void softReset();
	int startx;
	int starty;
	int endx;
	int endy;
	float heuristic(int _x1, int _y1);
	void addWall(int _x, int _y);
	void addBorderWalls(int _x, int _y, Direction direction);
	void removeWall(int _x, int _y);
	void setFire(int _x, int _y);
	void spreadFire();
	glm::vec2 getGridPosition(int _x, int _y);
	const int gridSize = 15;
	int cellSize = 40;
	void init();
private:
	//TEXTURES
	GameEngine::SpriteSheet Wall_Verticle;
	GameEngine::SpriteSheet Wall_Horizontal;
	//========
	int spreadTimer = 0;
	int x;
	int y;
	bool isFinished;
	bool oldIsFinished;
	Cell grid[15][15];
	Fire fireGrid[15][15];
	Tile tileGrid[15][15];
	GameEngine::SpriteBatch* sb;

	std::vector<Cell*> searched;
	std::vector<Cell*> finished;
	std::vector<Cell*> unsearched;
	bool isEndFound;
	bool oldIsEndFound;
	int progress;
};