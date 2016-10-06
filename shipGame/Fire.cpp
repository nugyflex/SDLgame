#include "Fire.h"

Fire::Fire()
{
}

Fire::Fire(GameEngine::SpriteBatch * _sb, int _x, int _y)
{
	sb = _sb;
	animation.init(sb, 18, 18, 2, 4, 5, 2, 2);
	animation.loadTexture("textures/fire.png");
	animation.reset();
	animation.setFrame(floor(((double)rand() / (RAND_MAX)) * 3));
	position.x = _x;
	position.y = _y;
}

Fire::~Fire()
{
}

void Fire::draw()
{
	animation.run();
	animation.draw(position.x, position.y);
}

void Fire::draw(int _x, int _y)
{
	animation.run();
	animation.draw(_x, _y);
}

void Fire::extinguish(float _amount)
{
	health -= _amount;
}

bool Fire::isExtinguished()
{
	if (health <= 0) {
		return true;
	}
	return false;
}
