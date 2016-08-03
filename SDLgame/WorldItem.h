#pragma once
#include <glm.hpp>
#include <GameEngine\BoundingBox.h>
#include <GameEngine\GameEngine.h>
class WorldItem {
public:
	WorldItem();
	~WorldItem();
	void init(float _x, float _y, float _w, float _h);
	BoundingBox* getBoundingBox();
	void setLightID(int _ID);
	void setSize(float _x, float _y);
	void setVel(float _x, float _y);
	void addToVel(float _x, float _y);
	void setPosition(float _x, float _y);
	void addToPosition(float _x, float _y);
	void setLightOffset(float _x, float _y);
	glm::vec2 getLightOffset();
	int getLightID();
	virtual void run();
	virtual GameEngine::Light getLight();
protected:
	BoundingBox boundingBox;
	glm::vec2 lightOffset;
	int lightID;
};