#include "MainGame.h"
#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>
#include <math.h>
#include <iostream>
#include <string>

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	maxLights(100)
{
    _camera.init(_screenWidth, _screenHeight);
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
	Lights.setMaxLights(200);
	Platforms.addPlatform(-200, 0, 800, 20);
	Platforms.addPlatform(-800, 0, 400, 20);
	Platforms.addPlatform(-400, 100, 400, 20);
	Platforms.addPlatform(-800, -600, 800, 20);
	Platforms.addPlatform(0, -1200, 800, 20);
	Platforms.addPlatform(-800, -1800, 800, 20);
	Platforms.addPlatform(0, -2400, 800, 20);
	Platforms.addPlatform(-800, -3000, 800, 20);
	Platforms.addPlatform(0, -3600, 800, 20);
	Platforms.addPlatform(-800, -4200, 800, 20);
	player.init(-50, 100, &WorldItems, &_spriteBatch);
	WorldItems.init(&Lights);
	for (int i = 0; i < 100; i++)
	{
		WorldItems.addItem(glowStick, 2*i, 100);
	}
	
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
	for (int j = 0; j < Platforms.getVectorSize(); j++)
	{
		cd.correctPosition(player.getBoundingBox(), Platforms.getBoundingBox(j));
		for (int i = 0; i < WorldItems.getVectorSize(); i++)
		{
			cd.correctPosition(WorldItems.getBoundingBox(i), Platforms.getBoundingBox(j));
		}
	}
	WorldItems.runItems();
	player.handleInput(&_inputManager);
	player.calcNewPos();
	_camera.followObject(player.getBoundingBox());
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
	/*
    if (_inputManager.isKeyPressed(SDLK_w)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
		lightPos.y+=10;
    }
    if (_inputManager.isKeyPressed(SDLK_s)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
		lightPos.y-=10;
    }
    if (_inputManager.isKeyPressed(SDLK_a)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
		lightPos.x-=10;
    }
    if (_inputManager.isKeyPressed(SDLK_d)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
		lightPos.x+=10;
    }*/
    if (_inputManager.isKeyPressed(SDLK_q)) {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDLK_e)) {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		if (!lastPressedL) {
			WorldItems.addItem(glowStick, mouseCoords.x, -mouseCoords.y);
		}
		lastPressedL = true;
	}
	else { lastPressedL = false; }
	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		if (!lastPressedR) {
			WorldItems.addItem(flare, mouseCoords.x, -mouseCoords.y);
		}
		lastPressedR = true;
	}
	else { lastPressedR = false; }
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {
	
	WorldItems.linkToLights();
	Lights.runFlicker();
	//std::cout << flare.x << "," << flare.y << "," << flare.z << "," << flare.w << std::endl;
    //Set the base depth to 1.0
    glClearDepth(1.0);
    //Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(1);
	
	glm::mat4 camera = _camera.getCameraMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//GameEngine::drawRect(0, 0, 500, 500, _camera.getCameraMatrix());
	glColor3f(0.0, 0.0, 0.0);
	GameEngine::drawLine(glm::vec2(50, 50), glm::vec2(-50, 100), camera);

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();
    //Enable the shader
    _colorProgram.use();
	GLint vignette = _colorProgram.getUniformLocation("vignette");
	glUniform2f(vignette, _camera.getPosition().x, _camera.getPosition().y);
	GLint ambientLight = _colorProgram.getUniformLocation("ambientLight");
	glUniform1f(ambientLight, 0.1);
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

	//-----------------PASSING LIGHTS INTO SHADER-----------------//
	Lights.addLightsToShader(&_colorProgram);
	//------------------------------------------------------------//
    _spriteBatch.begin();
    glm::vec4 pos(-100.0f, -100.0f, 500.0f, 500.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	glm::vec4 pos1(-1000.0f, 1000.0f, 2000.0f, -2000.0f);
	glm::vec4 uv1(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture newTexture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/b1.png");
	static GameEngine::GLTexture newTexture1 = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/b2.png");
	static GameEngine::GLTexture db = GameEngine::ResourceManager::getTexture("Textures/decentBackground.png");
	static GameEngine::GLTexture mb = GameEngine::ResourceManager::getTexture("Textures/meshBackground.png");
    GameEngine::Color color;
    color.r = 255;
    color.g = 0;
    color.b = 255;
    color.a = 255;
	_spriteBatch.draw(pos1, uv1, newTexture1.id, 0.0f, color, 0.5);
	_spriteBatch.draw(pos1, uv1, newTexture.id, 0.0f, color, 1);
	_spriteBatch.draw(glm::vec4(-3650 / 2, -2250 / 2, 3650, 2250) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.8, 0.8, 0, 0), uv1, db.id, 0.0f, color, 0);
	_spriteBatch.draw(glm::vec4(-9500 / 2, -5500 / 2, 9500, 5500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.6, 0.6, 0, 0), uv1, mb.id, 0.0f, color, 1);

    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	GameEngine::drawRect(300, 0, 600, 600, 1, color, &_spriteBatch);
	_spriteBatch.drawLine(glm::vec2(0, 0), glm::vec2(500, -100), color);
	Platforms.drawPlatforms(&_spriteBatch);
	player.draw();
	player.drawInventory(_camera.getPosition() - glm::vec2(_screenWidth/2, _screenHeight/2) - _camera.getVelocity());
    _spriteBatch.end();

    _spriteBatch.renderBatch();

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);


    //disable the shader
    _colorProgram.unuse();

    //Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}    
void MainGame::addLight(float x, float y, float r, float g, float b, float radius) {
	if (lightVector.size() < maxLights)
	{
		GameEngine::Light newLight;
		newLight.x = x;
		newLight.y = y;
		newLight.radius = radius;
		newLight.color = glm::vec3(r, g, b);
		lightVector.push_back(newLight);
		std::cout << "lights: " << lightVector.size() << std::endl;
	}
	else {
		std::cout << "Maximum amount of lights reached!" << std::endl;
	}
}