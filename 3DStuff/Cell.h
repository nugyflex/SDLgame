#pragma once
struct Cell
{
	bool isWall;
	float pressure;
	int x;
	int y;
	bool water;
	float waterPressure;
	float waterVelocity;
};