#pragma once
enum cellDirection {up, right, down, left};
struct Cell
{
	cellDirection direction;
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