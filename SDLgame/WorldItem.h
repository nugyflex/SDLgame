#pragma once
#include <glm.hpp>
#include <GameEngine\BoundingBox.h>
#include <GameEngine\GameEngine.h>
enum WorldItemType { flare, flareParticle, glowStick, default };
class WorldItem {
public:
	WorldItem();
	~WorldItem();
	void init(float _x, float _y, float _w, float _h);
	void init(float _x, float _y, float _w, float _h, int _timer);
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
	void runTimer();
	int getTimer();
	void setType(WorldItemType _type) { type = _type; }
	WorldItemType getType() { return type; }
	bool despawns;
protected:
	BoundingBox boundingBox;
	glm::vec2 lightOffset;
	int lightID;
	int deSpawnTimer = 1;
	WorldItemType type;
};