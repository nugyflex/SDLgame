
#include <math.h>
#include <iostream>
#include <string>

#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>

#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(400),
	_screenHeight(400),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(5.0f)
{
    _camera.init(_screenWidth, _screenHeight, -50, 3200);
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
	drawText.init(&_spriteBatch);
	_camera.setScreenShakeIntensity(10);
	grid = new Grid(&_spriteBatch);
	grid->runAI();
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

		grid->runAI();

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
    _spriteBatch.begin();
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	
	static GameEngine::GLTexture db = GameEngine::ResourceManager::getTexture("Textures/decentBackground.png");
    GameEngine::Color color;
    color.r = 255;
    color.g = 0;
    color.b = 255;
    color.a = 255;
	
	//_spriteBatch.draw(glm::vec4(-6500 / 2, -6500 / 2, 6500, 6500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.8, 0.8, 0, 0), uv, db.id, 0.0f, color, 0);
	grid->draw(0, 0);
	//GameEngine::drawRect(300, 0, 600, 600, 1, color, &_spriteBatch);

	_spriteBatch.end();
	
    _spriteBatch.renderBatch();

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);


    //disable the shader
    _colorProgram.unuse();

    //Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}    