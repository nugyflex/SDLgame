#pragma once
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GameEngine.h>
#include "Path.h"
#include <GameEngine\SpriteSheet.h>
#include "Grid.h"
class CrewMember {
public:
	CrewMember(GameEngine::SpriteBatch* _sb, Grid * _grid, int _x, int _y);
	~CrewMember();
	void draw();
	void getPath(int _x, int _y);
	void addPath(int _x, int _y);
	void followPath();
	glm::vec2 position;
private:
	Grid * grid;
	GameEngine::SpriteSheet walkNorth;
	GameEngine::SpriteSheet walkSouth;
	GameEngine::SpriteSheet walkEast;
	GameEngine::SpriteSheet walkWest;
	GameEngine::SpriteSheet standSouth;
	GameEngine::SpriteBatch* sb;
	glm::vec2 nextPosition;
	bool moved = true;
	float velocity;
	Path currentPath;
	bool isNewPath;
	bool isFirstPath = true;
	Path nextPath;
	int nextPathIndex = 0;
	bool finishedPath = true;
	bool atStart = false;
	glm::vec2 nextPathPos;
};