
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

    _spriteBatch.init();
    _fpsLimiter.init(_maxFPS);
	//drawText.init(&_spriteBatch);
	/*
	Boxes.push_back(new Box(0, 0, 0, 100, 10, 100));
	Boxes.push_back(new Box(0, 90, 0, 100, 10, 100));
	Boxes.push_back(new Box(0, 10, 0, 10, 80, 100));
	Boxes.push_back(new Box(90, 10, 0, 10, 80, 100));*/
	
	
	Boxes.push_back(new Box(0, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(20, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(40, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(60, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(80, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(100, 0, 1, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 1, 10, 10, 10));

	Boxes.push_back(new Box(0, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(20, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(40, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(60, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(80, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(100, 0, 120, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 120, 10, 10, 10));

	Boxes.push_back(new Box(0, 0, 20, 10, 10, 10));
	Boxes.push_back(new Box(0, 0, 40, 10, 10, 10));
	Boxes.push_back(new Box(0, 0, 60, 10, 10, 10));
	Boxes.push_back(new Box(0, 0, 80, 10, 10, 10));
	Boxes.push_back(new Box(0, 0, 100, 10, 10, 10));
	Boxes.push_back(new Box(0, 0, 120, 10, 10, 10));

	Boxes.push_back(new Box(120, 0, 20, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 40, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 60, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 80, 10, 10, 10));
	Boxes.push_back(new Box(120, 0, 100, 10, 10, 10));
	
	Boxes.push_back(new Box(-500, -100, -500, 1000, 10, 1000));
	//Boxes.push_back(new Box(0, 0, 0, 0.020, 2.000, 2.000));
	//Boxes.push_back(new Box(0, 1.980, 0, 2.000, 0.020, 2.000));
	//Boxes.push_back(new Box(1.980, 0, 0, 0.02, 2.000, 2.000));
	
	renderer = new Renderer(&_spriteBatch);
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
			Boxes.push_back(new Box(0, 0, 0, 20, 20, 20));
	}
	if (_inputManager.isKeyPressed(SDLK_f)) {
		lastF = true;
	}
	else {
		lastF = false;
	}
	//ROTATE:
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
	//TRANSLATING
	if (_inputManager.isKeyPressed(SDLK_q)) {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Transformations::translateBox(Boxes[i], 0, 1, 0);
		}
	}
	if (_inputManager.isKeyPressed(SDLK_e)) {
		for (int i = 0; i < Boxes.size(); i++)
		{
			Transformations::translateBox(Boxes[i], 0, -1, 0);
		}
	}
	if (_inputManager.isKeyPressed(SDLK_t)) {
		renderer->FOV += 0.01;
	}
	if (_inputManager.isKeyPressed(SDLK_y)) {
		renderer->FOV -= 0.01;
	}
	if (!_inputManager.isKeyPressed(SDLK_LCTRL)) {
		if (_inputManager.isKeyPressed(SDLK_w)) {
			for (int i = 0; i < Boxes.size(); i++)
			{
				
				Transformations::translateBox(Boxes[i], Transformations::getOffsetFromAngle(renderer->cameraPitch, 0.5).x, 0, Transformations::getOffsetFromAngle(renderer->cameraPitch, 0.5).y);
			}
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
			for (int i = 0; i < Boxes.size(); i++)
			{
				Transformations::translateBox(Boxes[i], Transformations::getOffsetFromAngle(renderer->cameraPitch - 3.1415 / 2, 2).x, 0, Transformations::getOffsetFromAngle(renderer->cameraPitch - 3.1415 / 2, 2).y);
			}
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			for (int i = 0; i < Boxes.size(); i++)
			{
				Transformations::translateBox(Boxes[i], -Transformations::getOffsetFromAngle(renderer->cameraPitch, 2).x, 0, -Transformations::getOffsetFromAngle(renderer->cameraPitch, 2).y);
			}
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			for (int i = 0; i < Boxes.size(); i++)
			{
				Transformations::translateBox(Boxes[i], Transformations::getOffsetFromAngle(renderer->cameraPitch + 3.1415/2, 2).x, 0, Transformations::getOffsetFromAngle(renderer->cameraPitch + 3.1415 / 2, 2).y);
			}
		}
	}
	else {
		if (_inputManager.isKeyPressed(SDLK_w)) {
			if (renderer->cameraRoll < 3.14/2)
			renderer->cameraRoll += 0.03;
			
		}
		if (_inputManager.isKeyPressed(SDLK_a)) {
				renderer->cameraPitch -= 0.05;
			//if (renderer->cameraPitch < 3.14*2) renderer->cameraPitch += 2*3.14;
			std::cout << renderer->cameraPitch << std::endl;
		}
		if (_inputManager.isKeyPressed(SDLK_s)) {
			if (renderer->cameraRoll > -3.14 / 2)
				renderer->cameraRoll -= 0.03;
		}
		if (_inputManager.isKeyPressed(SDLK_d)) {
			
			renderer->cameraPitch += 0.05;
			//if (renderer->cameraPitch > 3.14*2) renderer->cameraPitch -= 2*3.14;
		}
	}
	/*if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		//box->x = mouseCoords.x;
		//box->y = -mouseCoords.y;
		//box->updateVertices();
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		//box->z += 5;
		//box->updateVertices();
	}
	/*if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		grid->reducePressure(floor(((10 * 50 + 50) / 2 + mouseCoords.x) / 11), floor(((10 * 50 + 50) / 2 + -mouseCoords.y) / 11), 30);
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		//box->z -= 5;;
		//box->updateVertices();
	}*/
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {
	//Set the base depth to 1.0
	/*glClearDepth(1.0);
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
	_spriteBatch.begin();*/
	renderer->drawBackGround();
	for (int i = 0; i < Boxes.size(); i++) {
		renderer->drawBox(Boxes[i]);
		//Boxes[i]->yaw = 0.01;
		//Boxes[i]->pitch = 0.01;
		//Boxes[i]->roll = 0.01;
		Transformations::rotateBoxYaw(Boxes[i], Boxes[i]->yaw);
		Transformations::rotateBoxPitch(Boxes[i], Boxes[i]->pitch);
		Transformations::rotateBoxRoll(Boxes[i], Boxes[i]->roll);
	}
	renderer->drawAllFaces();
	renderer->resetFaces();
    //Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}    