#include "Flare.h"

Flare::Flare() {}
Flare::~Flare() {}
void Flare::run() {
	vel.y -= 0.1;
	position += vel;
}