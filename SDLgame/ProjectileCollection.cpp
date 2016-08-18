#include "ProjectileCollection.h"

ProjectileCollection::ProjectileCollection()
{
}

ProjectileCollection::~ProjectileCollection()
{
}

void ProjectileCollection::init(GameEngine::SpriteBatch * _sb)
{
	sb = _sb;
}

void ProjectileCollection::add(float _x, float _y, float _xVel, float _yVel)
{
	projectileVector.push_back(new Projectile());
	projectileVector[projectileVector.size() - 1]->init(sb, _x, _y, _xVel, _xVel);
}

void ProjectileCollection::draw()
{
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i]->draw();
	}
}

void ProjectileCollection::run()
{
	for (int i = 0; i < projectileVector.size(); i++) {
		projectileVector[i]->run();
	}
}
