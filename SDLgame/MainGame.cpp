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
	maxLights(10)
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
	GameEngine::Light newLight;
	for (int i = 0; i < 0; i++)
	{
		newLight.x = -200-(i * 20);
		newLight.y = -100;
		newLight.radius = 10;
		newLight.color = glm::vec3(1, 1, 1);
		lightVector.push_back(newLight);;
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

    if (_inputManager.isKeyPressed(SDLK_w)) {
        //_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
		lightPos.y+=10;
    }
    if (_inputManager.isKeyPressed(SDLK_s)) {
        //_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
		lightPos.y-=10;
    }
    if (_inputManager.isKeyPressed(SDLK_a)) {
        //_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
		lightPos.x-=10;
    }
    if (_inputManager.isKeyPressed(SDLK_d)) {
        //_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
		lightPos.x+=10;
    }
    if (_inputManager.isKeyPressed(SDLK_q)) {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDLK_e)) {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		//std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
		if (!lastPressed) {
			addLight(mouseCoords.x, -mouseCoords.y, ((double)rand() / (RAND_MAX)), ((double)rand() / (RAND_MAX)), ((double)rand() / (RAND_MAX)), ((double)rand() / (RAND_MAX)) * 100 + 20);
		}
		lastPressed = true;
	}
	else { lastPressed = false; }
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {

    //Set the base depth to 1.0
    glClearDepth(1.0);
    //Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(1);
	
	glm::mat4 camera = _camera.getCameraMatrix();
	glColor3f(1.0, 0.0, 0.0);
	//GameEngine::drawRect(0, 0, 500, 500, _camera.getCameraMatrix());
	glColor3f(0.0, 1.0, 0.0);
	GameEngine::drawLine(glm::vec2(50, 50), glm::vec2(-50, 100), camera);
/*
	glm::vec4 rect(0, 0, 500, 500);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0.1, 0);
	glVertex2f(0.1, 0.1);
	glVertex2f(0, 0.1);
	glEnd();*/
    //Enable the shader
    _colorProgram.use();

    //We are using texture unit 0
    glActiveTexture(GL_TEXTURE0);
    //Get the uniform location
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    //Tell the shader that the texture is in texture unit 0
    glUniform1i(textureLocation, 0);

    //Set the camera matrix
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();

    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	//GLint lightLocation = _colorProgram.getUniformLocation("lightPos");
	//glUniform2f(lightLocation, lightPos.x, lightPos.y);
	//GLint lightIntensity = _colorProgram.getUniformLocation("lightIntensity");
	//glUniform1f(lightIntensity, 1);
	//layout(std140) uniform MyBlock
	//{
	//	float myDataArray[size];
	//};
	//GLint lightsUniform = _colorProgram.getUniformLocation("lights"); // Getting location
	//float x[9];
	//glUniform1f(lightsUniform, x);
	//glGetUniformBlockIndex​(_colorProgram, "MyBlock");
	//GameEngine::Color color1;
	//color1.r = 255;
	//color1.g = 255;
	//color1.b = 255;
	//color1.a = 255;
	//std::vector<GameEngine::Color> data;
	//for (unsigned int i = 0; i < 5; i++)
	//{
	//	data.push_back(color1);
	//}
	//GLuint texture1;
	//glGenTextures( 1, &texture1);
	//glActiveTexture(GL_TEXTURE0+ texture1);
	//glBindTexture(GL_TEXTURE_1D, texture1);
	//glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 5, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
	//GLint test1 = _colorProgram.getUniformLocation("test1");
	//glUniform1i(test1, texture1);
	//glActiveTexture(GL_TEXTURE0);

	//-----------------PASSING LIGHTS INTO SHADER-----------------//

	const int size = 100;
	float lightColourArray[size*3];
	//std::cout << "lights: " << lightVector.size() << std::endl;
	for (unsigned int i = 0; i < lightVector.size(); i++)
	{
		lightColourArray[i * 3] = lightVector[i].color.r;
		lightColourArray[(i * 3) + 1] = lightVector[i].color.g;
		lightColourArray[(i * 3) + 2] = lightVector[i].color.b;
	}
	float lightPositionArray[size*2];
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
	GLint lightArraySize = _colorProgram.getUniformLocation("lightArraySize");
	glUniform1i(lightArraySize, lightVector.size());
	GLint lightColours = _colorProgram.getUniformLocation("lightColours");
	glUniform1fv(lightColours, size*3, lightColourArray );
	GLint lightPositions = _colorProgram.getUniformLocation("lightPositions");
	glUniform1fv(lightPositions, size*2, lightPositionArray);
	GLint lightRadii = _colorProgram.getUniformLocation("lightRadii");
	glUniform1fv(lightRadii, size, lightRadiusArray);
	//------------------------------------------------------------//
    _spriteBatch.begin();
    glm::vec4 pos(-100.0f, -100.0f, 500.0f, 500.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	glm::vec4 pos1(-1000.0f, 1000.0f, 2000.0f, -2000.0f);
	glm::vec4 uv1(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture 
		newTexture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/AngryCloud.png");
    GameEngine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	_spriteBatch.draw(pos1, uv1, newTexture.id, 0.0f, color);

    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	GameEngine::drawRect(300, 0, 600, 600, color, &_spriteBatch);
	
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