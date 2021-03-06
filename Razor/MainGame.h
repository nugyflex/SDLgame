#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <vector>

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
	void updateGame();
    GameEngine::Window _window;
    int _screenWidth;
    int _screenHeight;
    GameState _gameState;

    GameEngine::GLSLProgram _colorProgram;
    GameEngine::Camera2D _camera;

    GameEngine::SpriteBatch spriteBatch;

    GameEngine::InputManager _inputManager;
    GameEngine::FpsLimiter _fpsLimiter;
    
    float _maxFPS;
    float _fps;
    float _time;
	bool lastPressedL = false;
	bool lastPressedR = false;
};

