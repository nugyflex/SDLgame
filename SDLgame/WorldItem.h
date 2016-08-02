#pragma once
#include <glm.hpp>
class WorldItem {
public:
	WorldItem();
	~WorldItem();
	void init(float _x, float _y, float _w, float _h);
	glm::vec2 getPosition();
	glm::vec2 getVel();
	glm::vec2 getSize();
	glm::vec4 getRect();
	void setLightID(int _ID);
	void setSize(glm::vec2 _size);
	void setVel(glm::vec2 _vel);
	void addToVel(glm::vec2 _vel);
	void setPosition(glm::vec2 _vel);
	void addToPosition(glm::vec2 _vel);
	void setLightOffset(glm::vec2 _offset);
	glm::vec2 getLightOffset();
	int getLightID();
	virtual void run() {};
protected:
	glm::vec2 position;
	glm::vec2 vel;
	glm::vec2 size;
	glm::vec2 lightOffset;
	int lightID;
};