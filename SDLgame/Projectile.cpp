#include "Projectile.h"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::init(GameEngine::SpriteBatch* _sb, float _x, float _y, float _xVel, float _yVel)
{
	position.x = _x;
	position.y = _y;
	velocity.x = _xVel;
	velocity.y = _yVel;
	lastPosition = position;
	drawPosition = lastPosition;
	sb = _sb;
}

void Projectile::calcNewPos()
{
	position += velocity;
}
void Projectile::run()
{
	drawPosition = lastPosition;
	lastPosition = position;
	calcNewPos();
}

void Projectile::draw()
{
	sb->drawLine(position, drawPosition, 255, 150, 0, 255);
}
