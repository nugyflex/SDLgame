﻿
#include <math.h>
#include <iostream>
#include <string>
#include <thread>

#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>

#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(1000),
	_screenHeight(1000),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight, 0, 0);
}

//Destructor
MainGame::~MainGame()
{
}

//This runs the game
void MainGame::run() {
	initSystems();


	//This only returns when the game ends
	gameLoop();
}
//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {

	GameEngine::init();

	_window.create("Game Engine", _screenWidth, _screenHeight, 0);

	initShaders();

	spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
	//drawText.init(&_spriteBatch);
	_camera.setScreenShakeIntensity(10);
	grid = new Grid(&spriteBatch);
}

void MainGame::initShaders() {
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.addAttribute("test");
	_colorProgram.linkShaders();

}

//This is the main game loop for our program
void MainGame::gameLoop() {

	//Will loop until we set _gameState to EXIT
	while (_gameState != GameState::EXIT) {

		_fpsLimiter.begin();

		processInput();
		_time += 0.1;

		_camera.update();
		//std::cout << _fps << std::endl;
		updateGame();

		drawGame();

		_fps = _fpsLimiter.end();

		//print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000) {
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}
	}
}
void MainGame::updateGame() {
	_inputManager.lastMouseR = _inputManager.isKeyPressed(SDL_BUTTON_RIGHT);
	_inputManager.lastMouseL = _inputManager.isKeyPressed(SDL_BUTTON_LEFT);
	_inputManager.lastMouseM = _inputManager.isKeyPressed(SDL_BUTTON_MIDDLE);
}
//Processes input with SDL
void MainGame::processInput() {
	SDL_Event evnt;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			//std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		//grid->addPressure(floor(((10*50 + 50)/2 + mouseCoords.x)/11), floor(((10 * 50 + 50)/2 + -mouseCoords.y) / 11), 30);
		//grid->addWater(floor(((10 * 50 + 50) / 2 + mouseCoords.x) / 11), floor(((10 * 50 + 50) / 2 + -mouseCoords.y) / 11));
		std::cout << grid->getValue(floor(((grid->cellSize * grid->gridSize /*+ grid->gridSize*/) / 2 + mouseCoords.x) / (grid->cellSize+1)), floor(((grid->cellSize * grid->gridSize /*+ grid->gridSize*/) / 2 + -mouseCoords.y)/ (grid->cellSize + 1))) << std::endl;
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		//grid->reducePressure(floor(((10 * 50 + 50) / 2 + mouseCoords.x) / 11), floor(((10 * 50 + 50) / 2 + -mouseCoords.y) / 11), 30);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		grid->reset();
		if (_inputManager.isKeyPressed(SDLK_LCTRL))
		{
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);
			//grid->removeWall(floor(((10 * 50 + 50) / 2 + mouseCoords.x) / 11), floor(((10 * 50 + 50) / 2 + -mouseCoords.y) / 11));
		}
		else
		{
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);
			//grid->addWall(floor(((10 * 50 + 50) / 2 + mouseCoords.x) / 11), floor(((10 * 50 + 50) / 2 + -mouseCoords.y) / 11));
		}
	}
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {
	//Set the base depth to 1.0
	glClearDepth(1.0);
	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(1);

	glm::mat4 camera = _camera.getCameraMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();
	//Enable the shader
	_colorProgram.use();
	//We are using texture unit 0
	glActiveTexture(GL_TEXTURE0);
	//Get the uniform location
	GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
	//Tell the shader that the texture is in texture unit 0
	glUniform1i(textureLocation, 0);

	//Set the camera matrixx
	GLint pLocation = _colorProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();

	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
	spriteBatch.begin();
	grid->draw(0, 0);

	spriteBatch.end();

	spriteBatch.renderBatch();

	//unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);


	//disable the shader
	_colorProgram.unuse();

	//Swap our buffer and draw everything to the screen!
	_window.swapBuffer();
}