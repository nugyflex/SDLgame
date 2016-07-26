#include "MainGame.h"
#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>

#include <iostream>
#include <string>

//Constructor, just initializes private member variables
MainGame::MainGame() : 
    _screenWidth(1024),
    _screenHeight(768), 
    _time(0.0f),
    _gameState(GameState::PLAY),
    _maxFPS(60.0f)
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
		std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
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

	GLint lightLocation = _colorProgram.getUniformLocation("lightPos");
	glUniform2f(lightLocation, lightPos.x, lightPos.y);
	GLint lightIntensity = _colorProgram.getUniformLocation("lightIntensity");
	glUniform1f(lightIntensity, 1);
	//layout(std140) uniform MyBlock
	//{
	//	float myDataArray[size];
	//};
	//GLint lightsUniform = _colorProgram.getUniformLocation("lights"); // Getting location
	//float x[9];
	//glUniform1f(lightsUniform, x);
	//glGetUniformBlockIndex​(_colorProgram, "MyBlock");
	glTexBufferRange​(GLenum target​, GL_R32F​, GLuint buffer​, GLintptr offset​, GLsizeiptr size​);
    _spriteBatch.begin();

    glm::vec4 pos(-100.0f, -100.0f, 500.0f, 500.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	glm::vec4 pos1(-1000.0f, 1000.0f, 2000.0f, -2000.0f);
	glm::vec4 uv1(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture newTexture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/AngryCloud.png");
    GameEngine::Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	_spriteBatch.draw(pos1, uv1, newTexture.id, 0.0f, color, 2);
	GLint renderLighting = _colorProgram.getUniformLocation("renderLighting");
	glUniform1f(renderLighting, 1);
    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color, 1);
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