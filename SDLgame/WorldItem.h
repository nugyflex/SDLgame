#pragma once
#include <glm.hpp>
#include <GameEngine\BoundingBox.h>
#include <GameEngine\GameEngine.h>
#include <GameEngine\SpriteSheet.h>
#include <GameEngine\SpriteBatch.h>
enum WorldItemType { flare, flareParticle, glowStick, default, explosion, fireParticle, explosionParticle };
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
	void drawSpriteSheet();
	bool hasSpriteSheet = false;
	virtual void loadSpriteSheet();
	void linkSpriteBatch(GameEngine::SpriteBatch* _sb) { sb = _sb; }
	virtual void draw();
	bool canBePickedUp;
	bool centerLight = false;
protected:
	BoundingBox boundingBox;
	glm::vec2 lightOffset;
	glm::vec2 spriteSheetOffset = glm::vec2(0,0);
	int lightID;
	int deSpawnTimer = 1;
	WorldItemType type;
	GameEngine::SpriteSheet spriteSheet;
	bool centerSpriteSheet = false;
	GameEngine::SpriteBatch* sb;
};