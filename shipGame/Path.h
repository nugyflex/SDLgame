#pragma once
enum Direction { up, right, down, left, finished1 };
struct Path
{
	Direction directionarray[200];
	void init() { for (int i = 0; i < 200; i++) { directionarray[i] = finished1; } }
};