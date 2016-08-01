#pragma once
#include <GameEngine/GameEngine.h>
#include <GameEngine/GLSLProgram.h>
#include <vector>
class LightCollection {
public:
	LightCollection();
	~LightCollection();
	void addLight(float x, float y, float r, float g, float b, float radius);
	void addLightsToShader(GameEngine::GLSLProgram* _shaderProgram);
	void setMaxLights(int _maxlights);
	void changeLightPosition(int _ID, float _x, float _y);
private:
	int maxLights;
	int lastLightID = 0;
	std::vector<GameEngine::Light> lightVector;
	int getVectorIndexByID(int _ID);
};