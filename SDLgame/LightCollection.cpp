#include <iostream>

#include "LightCollection.h"
#include "GameEngine/Errors.h"

LightCollection::LightCollection()
{

}
LightCollection::~LightCollection()
{

}
void LightCollection::setMaxLights(int _maxlights) {
	maxLights = _maxlights;
}
int LightCollection::addLight(float x, float y, float r, float g, float b, float radius, glm::vec2 _flickerRange) {
	if (lightVector.size() < maxLights)
	{
		GameEngine::Light newLight;
		newLight.x = x;
		newLight.y = y;
newLight.radius = radius;
newLight.color = glm::vec3(r, g, b);
newLight.flicker = true;
newLight.flickerRange = _flickerRange;
newLight.ID = lastLightID + 1;
lastLightID++;
lightVector.push_back(newLight);
//std::cout << "lights: " << lightVector.size() << std::endl;
return newLight.ID;
	}
	else {
		std::cout << "Maximum amount of lights reached!" << std::endl;
		return 0;
	}
}
int LightCollection::addLight(float x, float y, float r, float g, float b, float radius) {
	if (lightVector.size() < maxLights)
	{
		GameEngine::Light newLight;
		newLight.x = x;
		newLight.y = y;
		newLight.radius = radius;
		newLight.color = glm::vec3(r, g, b);
		newLight.flicker = false;
		newLight.ID = lastLightID + 1;
		lastLightID++;
		lightVector.push_back(newLight);
		//std::cout << "lights: " << lightVector.size() << std::endl;
		return newLight.ID;
	}
	else {
		std::cout << "Maximum amount of lights reached!" << std::endl;
		return 0;
	}
}
int LightCollection::addLight(GameEngine::Light _light) {
	if (lightVector.size() < maxLights)
	{
		_light.ID = lastLightID + 1;
		lastLightID++;
		lightVector.push_back(_light);
		//std::cout << "lights: " << lightVector.size() << std::endl;
		return _light.ID;
	}
	else {
		std::cout << "Maximum amount of lights reached!" << std::endl;
		return -1;
	}
}
void LightCollection::addLightsToShader(GameEngine::GLSLProgram* _shaderProgram) {
	const int size = 200;
	float lightColourArray[size * 3];
	//std::cout << "lights: " << lightVector.size() << std::endl;
	for (unsigned int i = 0; i < lightVector.size(); i++)
	{
		lightColourArray[i * 3] = lightVector[i].color.r;
		lightColourArray[(i * 3) + 1] = lightVector[i].color.g;
		lightColourArray[(i * 3) + 2] = lightVector[i].color.b;
	}
	float lightPositionArray[size * 2];
	for (unsigned int i = 0; i < lightVector.size(); i++)
	{
		lightPositionArray[i * 2] = lightVector[i].x;
		lightPositionArray[(i * 2) + 1] = lightVector[i].y;
	}
	float lightRadiusArray[size];
	for (unsigned int i = 0; i < lightVector.size(); i++)
	{
		lightRadiusArray[i] = lightVector[i].radius;
	}
	GLint lightArraySize = _shaderProgram->getUniformLocation("lightArraySize");
	glUniform1i(lightArraySize, lightVector.size());
	GLint lightColours = _shaderProgram->getUniformLocation("lightColours");
	glUniform1fv(lightColours, size * 3, lightColourArray);
	GLint lightPositions = _shaderProgram->getUniformLocation("lightPositions");
	glUniform1fv(lightPositions, size * 2, lightPositionArray);
	GLint lightRadii = _shaderProgram->getUniformLocation("lightRadii");
	glUniform1fv(lightRadii, size, lightRadiusArray);
}
int LightCollection::getVectorIndexByID(int _ID) {
	for (int i = 0; i < lightVector.size(); i++) {
		if (lightVector[i].ID == _ID) {
			return i;
		}
	}
	std::cout << "No Light found with ID " << _ID << std::endl;
	return -1;
}
void LightCollection::changePosition(int _ID, float _x, float _y) {
	int index = getVectorIndexByID(_ID);
	lightVector[index].x = _x;
	lightVector[index].y = _y;
}
void LightCollection::changeRadius(int _ID, float _radius) {
	lightVector[getVectorIndexByID(_ID)].radius = _radius;
}
void LightCollection::addToRadius(int _ID, float _radius) {
	if (lightVector[getVectorIndexByID(_ID)].radius > 0 || _radius > 0)
	{
		lightVector[getVectorIndexByID(_ID)].radius += _radius;
		if (lightVector[getVectorIndexByID(_ID)].radius  < 0) {
			lightVector[getVectorIndexByID(_ID)].radius = 0;
		}
	}
}
float LightCollection::getRadius(int _ID)
{
	return lightVector[getVectorIndexByID(_ID)].radius;
}
void LightCollection::runFlicker() {
	for (int i = 0; i < lightVector.size(); i++) {
		if (lightVector[i].flicker) {
			lightVector[i].radius = ((double)rand() / (RAND_MAX)) * (lightVector[i].flickerRange.y - lightVector[i].flickerRange.x) + lightVector[i].flickerRange.x;
		}
	}
}
void LightCollection::removeLight(int _ID) {
	
	int index = getVectorIndexByID(_ID);
	if (index != -1) {
		lightVector.erase(lightVector.begin() + index);
	}
}