#include "CrewMember.h"
#include <iostream>
CrewMember::CrewMember(GameEngine::SpriteBatch * _sb, Grid * _grid, int _x, int _y)
{
	grid = _grid;
	sb = _sb;
	position.x = _x;
	position.y = _y;
	velocity = 4;
	walkNorth.init(sb, 16, 16, 2, 10, 5, -16, -16);
	walkNorth.loadTexture("textures/walkingNorth.png");
	walkSouth.init(sb, 16, 16, 2, 10, 5, -16, -16);
	walkSouth.loadTexture("textures/walkingSouth.png");
	walkEast.init(sb, 16, 16, 2, 10, 5, -16, -16);
	walkEast.loadTexture("textures/walkingEast.png");
	walkWest.init(sb, 16, 16, 2, 10, 5, -16, -16);
	walkWest.loadTexture("textures/walkingWest.png");
	standSouth.init(sb, 16, 16, 2, 1, 5, -16, -16);
	standSouth.loadTexture("textures/standingSouth.png");
}

CrewMember::~CrewMember()
{
}

void CrewMember::draw()
{
	GameEngine::Color color;
	color.r = 0;
	color.b = 255;
	color.g = 255;
	color.a = 255;
	//GameEngine::drawRect(position.x-10, position.y-10, 20, 20, 1, color, sb);
	if (position.x < nextPosition.x && position.y == nextPosition.y) {
		walkEast.run();
		walkEast.draw(position.x, position.y);
	}
	else if (position.x > nextPosition.x && position.y == nextPosition.y) {
		walkWest.run();
		walkWest.draw(position.x, position.y);
	}
	else if (position.x == nextPosition.x && position.y < nextPosition.y) {
		walkNorth.run();
		walkNorth.draw(position.x, position.y);
	}
	else if (position.x == nextPosition.x && position.y > nextPosition.y) {
		walkSouth.run();
		walkSouth.draw(position.x, position.y);
	}
	else {
		standSouth.draw(position.x, position.y);
	}
}


void CrewMember::addPath(int _x, int _y)
{
	/*currentPath = _path;
	nextPathIndex = 0;
	finishedPath = false;
	nextPosition.y = 0;
	nextPosition.x = 0;
	atStart = false;
	moved = true;
	nextPosition = position;*/
	if (isFirstPath) {
		grid->setStart(floor(((grid->cellSize* grid->gridSize + grid->gridSize) / 2 + _x) / (grid->cellSize + 1)), floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + _y) / (grid->cellSize + 1)));
		grid->softReset();
		grid->setEnd(floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + position.x) / (grid->cellSize + 1)), floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + position.y) / (grid->cellSize + 1)));
		currentPath = grid->getPath();
		nextPathIndex = 0;
		finishedPath = false;
		nextPosition.y = 0;
		nextPosition.x = 0;
		atStart = false;
		moved = true;
		nextPosition = position;
		isFirstPath = false;
	}
	else {

		nextPathPos = glm::vec2(_x, _y);
		isNewPath = true;
	}
}

void CrewMember::getPath(int _x, int _y)
{
	grid->setStart(floor(((grid->cellSize* grid->gridSize + grid->gridSize) / 2 + _x) / (grid->cellSize + 1)), floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + _y) / (grid->cellSize + 1)));
	grid->softReset();
	grid->setEnd(floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + position.x) / (grid->cellSize + 1)), floor(((grid->cellSize * grid->gridSize + grid->gridSize) / 2 + position.y) / (grid->cellSize + 1)));
	currentPath = grid->getPath();
	nextPathIndex = 0;
	finishedPath = false;
	nextPosition.y = 0;
	nextPosition.x = 0;
	atStart = false;
	moved = true;
	nextPosition = position;
	isFirstPath = false;
}

void CrewMember::followPath()
{
	if (position.x >= nextPosition.x - velocity && position.x <= nextPosition.x + velocity && position.y >= nextPosition.y - velocity && position.y <= nextPosition.y + velocity) {
		position = nextPosition;
		moved = true;
		if (isNewPath) {
			getPath(nextPathPos.x, nextPathPos.y);
			isNewPath = false;
		}
	}
	if (!finishedPath && moved) {
		switch (currentPath.directionarray[nextPathIndex]) {
		case up:
			nextPosition = position;
			nextPosition.y += 41;
			break;
		case down:
			nextPosition = position;
			nextPosition.y -= 41;
			break;
		case left:
			nextPosition = position;
			nextPosition.x -= 41;
			break;
		case right:
			nextPosition = position;
			nextPosition.x += 41;
			break;
		case finished1:
			finishedPath = true;
			break;
		}
		moved = false;
		nextPathIndex++;
	}
	if (position.x < nextPosition.x && position.y == nextPosition.y) {
		position.x += velocity;
	}
	else if (position.x > nextPosition.x && position.y == nextPosition.y) {
		position.x -= velocity;
	}
	else if (position.x == nextPosition.x && position.y < nextPosition.y) {
		position.y += velocity;
	}
	else if (position.x == nextPosition.x && position.y > nextPosition.y) {
		position.y -= velocity;
	}/*
	if (position.x >= nextPosition.x - velocity && position.x <= nextPosition.x + velocity && position.y >= nextPosition.y - velocity && position.y <= nextPosition.y + velocity) {
		position = nextPosition;
		moved = true;
		if (isNewPath) {
			getPath(nextPathPos.x, nextPathPos.y);
			isNewPath = false;
		}
	}*/
}
