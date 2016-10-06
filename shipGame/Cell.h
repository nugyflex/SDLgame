#pragma once
#include "Path.h"
struct Walls { bool left = false; bool right = false; bool up = false; bool down = false; };
struct Cell
{
	Direction direction;
	Walls walls;
	bool isWall;
	bool searched;
	bool finished;
	bool isNew;
	bool isEnd;
	bool isStart;
	bool isPath;
	int score;
	float priority;
	int x;
	int y;
	int noise;
};