#pragma once
#include <GameEngine/GameEngine.h>
#include <GameEngine/GLSLProgram.h>
#include <vector>
class LightCollection {
public:
	LightCollection();
	~LightCollection();
	int addLight(float x, float y, float r, float g, float b, float radius);
	int addLight(float x, float y, float r, float g, float b, float radius, glm::vec2 _flickerRange);
	int addLight(GameEngine::Light _light);
	void removeLight(int _ID);
	void addLightsToShader(GameEngine::GLSLProgram* _shaderProgram);
	void setMaxLights(int _maxlights); 
	void changePosition(int _ID, float _x, float _y);
	void changeRadius(int _ID, float radius);
	void addToRadius(int _ID, float radius);
	void runFlicker();
private:
	int maxLights;
	int lastLightID = 0;
	std::vector<GameEngine::Light> lightVector;
	int getVectorIndexByID(int _ID);
};