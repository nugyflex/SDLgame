#pragma once
#include <glm.hpp>
#include "WorldItem.h"
class Flare : public WorldItem {
public:
	Flare();
	~Flare();
	void run();
};