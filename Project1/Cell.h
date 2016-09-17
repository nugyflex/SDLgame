#pragma once
enum cellDirection {up, right, down, left};
class Cell
{
public:
	cellDirection direction;
	bool isWall;
	bool searched;
	bool finished;
	bool isNew;
	bool isEnd;
	bool isStart;
	bool isPath;
	int x;
	int y;
private:
};