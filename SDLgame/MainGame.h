#pragma once

#include <SDL.h>
#include <GL/glew.h>

#include <GameEngine/GameEngine.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GLTexture.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/Window.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/Timing.h>
#include <GameEngine/CollisionDetection.h>

#include <GameEngine/SpriteBatch.h>

#include <GameEngine/Camera2D.h>

#include <vector>

#include "LightCollection.h"
#include "WorldItemCollection.h"
#include "PlatformCollection.h"

enum class GameState {PLAY, EXIT};

//Our example game class, just for testing purposes right now
class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();
	void addLight(float x, float y, float r, float g, float b, float radius);
private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    GameEngine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    GameEngine::GLSLProgram _colorProgram;
    GameEngine::Camera2D _camera;

    GameEngine::SpriteBatch _spriteBatch;

    GameEngine::InputManager _inputManager;
    GameEngine::FpsLimiter _fpsLimiter;
    
    float _maxFPS;
    float _fps;
    float _time;
	glm::vec2 lightPos = glm::vec2(0,0);
	std::vector<GameEngine::Light> lightVector;
	bool lastPressed = false;
	int maxLights;
	LightCollection Lights;
	glm::vec2 flareVel = glm::vec2(0, 0);
	glm::vec4 rect1 = glm::vec4(-500, -50, 1000, 100);
	GameEngine::CollisionDetection cd;
	WorldItemCollection WorldItems;
	PlatformCollection Platforms;
};

