#include "Flare.h"

Flare::Flare() {}
Flare::~Flare() {}
void Flare::run() {
	boundingBox.yv -= 0.1;
	boundingBox.x += boundingBox.xv;
	boundingBox.y += boundingBox.yv;
}