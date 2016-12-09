
#include <math.h>
#include <iostream>
#include <string>
#include <thread>

#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>

#include "MainGame.h"
#include "Transformations.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(800),
	_screenHeight(800),
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
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//drawText.init(&_spriteBatch);
	/*
	Boxes.push_back(new Box(0, 0, 0, 100, 10, 100));
	Boxes.push_back(new Box(0, 90, 0, 100, 10, 100));
	Boxes.push_back(new Box(0, 10, 0, 10, 80, 100));
	Boxes.push_back(new Box(90, 10, 0, 10, 80, 100));*/
	
	//Boxes.push_back(new Box(0, 0, 0, 100, 100, 100));

	//

	Boxes.push_back(new Box(-500, 100, -500, 500, 10, 500));
	Boxes.push_back(new Box(1, 50, 1, 10, 10, 10));
	Boxes[1]->velocity.y = 0.2;
	//Boxes.push_back(new Box(0, 0, 0, 0.020, 2.000, 2.000));
	//Boxes.push_back(new Box(0, 1.980, 0, 2.000, 0.020, 2.000));
	//Boxes.push_back(new Box(1.980, 0, 0, 0.02, 2.000, 2.000));
	
	renderer = new Renderer(&spriteBatch);
	renderer->setScreenSize(800, 800);
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
        if (frameCounter == 200) {
            std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}
void MainGame::updateGame() {
	_inputManager.lastMouseR = _inputManager.isKeyPressed(SDL_BUTTON_RIGHT);
	_inputManager.lastMouseL = _inputManager.isKeyPressed(SDL_BUTTON_LEFT);
	_inputManager.lastMouseM = _inputManager.isKeyPressed(SDL_BUTTON_MIDDLE);
	//Transformations::rotateVertex();
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
	if (_inputManager.isKeyPressed(SDLK_f) && !lastF) {
			Boxes.push_back(new Box(renderer->cameraPosition.x-10, renderer->cameraPosition.y-10, renderer->cameraPosition.z - 10, 20, 20, 20));
	}
	if (_inputManager.isKeyPressed(SDLK_f)) {
		lastF = true;
	}
	else {
		lastF = false;
	}
	//ROTATE BOXES:
	if (_inputManager.isKeyPressed(SDLK_g)) {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->pitch = 0.02;
		}
	}
	else {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->pitch = 0;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_h)) {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->yaw = 0.02;
		}
	}
	else {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->yaw = 0;
		}
	}
	if (_inputManager.isKeyPressed(SDLK_j)) {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->roll = 0.02;
		}
	}
	else {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Boxes[i]->roll = 0;
		}
	}
	float vel = 1.5;
	//MOVING CAMERA
	if (_inputManager.isKeyPressed(SDLK_q)) {
		renderer->addToCameraPosition( 0, vel, 0);
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		renderer->addToCameraPosition(0, -vel, 0);
	}
	if (_inputManager.isKeyPressed(SDLK_t)) {
		renderer->FOV += 0.01;
	}
	if (_inputManager.isKeyPressed(SDLK_y)) {
		renderer->FOV -= 0.01;
	}
	if (!_inputManager.isKeyPressed(SDLK_LCTRL)) {
		
		if (_inputManager.isKeyPressed(SDLK_w)) {
			renderer->addToCameraPosition(-Transformations::getOffsetFromAngle(renderer->cameraPitch, vel).x, 0, -Transformations::getOffsetFromAngle(renderer->cameraPitch, vel).y);
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			renderer->addToCameraPosition(-Transformations::getOffsetFromAngle(renderer->cameraPitch - 3.1415 / 2, vel).x, 0, -Transformations::getOffsetFromAngle(renderer->cameraPitch - 3.1415 / 2, vel).y);
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			renderer->addToCameraPosition(Transformations::getOffsetFromAngle(renderer->cameraPitch, vel).x, 0, Transformations::getOffsetFromAngle(renderer->cameraPitch, vel).y);
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			renderer->addToCameraPosition(-Transformations::getOffsetFromAngle(renderer->cameraPitch + 3.1415 / 2, vel).x, 0, -Transformations::getOffsetFromAngle(renderer->cameraPitch + 3.1415 / 2, vel).y);
		}
	}
	else {
		//ROTATING CAMERA
		if (_inputManager.isKeyPressed(SDLK_w)) {
			if (renderer->cameraRoll < 3.14/2)
			renderer->cameraRoll += 0.03;
			
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
				renderer->cameraPitch -= 0.05;
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			if (renderer->cameraRoll > -3.14 / 2)
				renderer->cameraRoll -= 0.03;
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			
			renderer->cameraPitch += 0.05;
		}
	}
}

void MainGame::drawGame() {
	for (int i = 0; i < Boxes.size(); i++) {
		renderer->drawBox(Boxes[i]);
		Transformations::rotateBoxYaw(Boxes[i], Boxes[i]->yaw);
		Transformations::rotateBoxPitch(Boxes[i], Boxes[i]->pitch);
		Transformations::rotateBoxRoll(Boxes[i], Boxes[i]->roll);
		Boxes[i]->updatePosition();
		Boxes[i]->updateVertices();
	}
	renderer->collisionDetection3D(Boxes[1], Boxes[0]);
	renderer->drawAllFaces();
	renderer->resetFaces();
    _window.swapBuffer();
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}    