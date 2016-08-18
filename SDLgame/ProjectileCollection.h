#pragma once
#include <vector>
#include "Projectile.h"
#include <GameEngine\CollisionDetection.h>
class ProjectileCollection {
public:
	ProjectileCollection();
	~ProjectileCollection();
	void init(GameEngine::SpriteBatch* _sb);
	void add(float _x, float _y, float _xVel, float _yVel);
	void draw();
	void run();
	int getVectorSize() { return projectileVector.size(); }
private:
	void remove(int _index);
	std::vector<Projectile*> projectileVector;
	GameEngine::SpriteBatch* sb;
	GameEngine::CollisionDetection cd;
};
