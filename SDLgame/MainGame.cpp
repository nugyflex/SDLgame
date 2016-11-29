
#include <math.h>
#include <iostream>
#include <string>

#include <GameEngine/Errors.h>
#include <GameEngine/ResourceManager.h>

#include "MainGame.h"

//Constructor, just initializes private member variables
MainGame::MainGame() :
	_screenWidth(1000),
	_screenHeight(800),
	_time(0.0f),
	_gameState(GameState::PLAY),
	_maxFPS(60.0f),
	maxLights(100)
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

    spriteBatch.init();
    _fpsLimiter.init(_maxFPS);
	projectiles.init(&spriteBatch);
	Lights.setMaxLights(200);
	Lights.addLight(-400, -7100, 0.2, 0.2, 1, 100);
	Lights.addLight(0, 10000, 1, 1, 1, 15000);
	Platforms.addPlatform(500, 3080, 100, 16);
	Platforms.addPlatform(-200, 3000, 800, 16);
	Platforms.addPlatform(-800, 3000, 400, 16);
	Platforms.addPlatform(-400, 3040, 400, 16);
	Platforms.addPlatform(400, 3040, 400, 16);
	Platforms.addPlatform(-1400, 2700, 400, 16);
	Platforms.addPlatform(-1400, 2400, 400, 16);
	Platforms.addPlatform(-1400, 2100, 400, 16);
	Platforms.addPlatform(-1400, 1800, 400, 16);
	Platforms.addPlatform(-800, 1500, 800, 16);
	Platforms.addPlatform(0, 1800, 800, 16);
	Platforms.addPlatform(-800, 1200, 800, 16);
	Platforms.addPlatform(0, 600, 800, 16);
	Platforms.addPlatform(-800, 0, 800, 16);
	Platforms.addPlatform(0, -600, 800, 16);
	Platforms.addPlatform(-800, -1200, 800, 16);
	Platforms.addPlatform(0, -1800, 800, 16);
	Platforms.addPlatform(-800, -2400, 800, 16);
	Platforms.addPlatform(0, -3000, 800, 16);
	Platforms.addPlatform(-800, -3600, 800, 16);
	Platforms.addPlatform(0, -4200, 800, 16);
	Platforms.addPlatform(-800, -4800, 800, 16);
	Platforms.addPlatform(0, -5400, 800, 16);
	Platforms.addPlatform(-800, -6000, 800, 16);
	Platforms.addPlatform(0, -6600, 800, 16);
	Platforms.addPlatform(-800, -7200, 800, 16);
	player.init(360, 3400, &WorldItems, &spriteBatch, &drawText, &projectiles, &cd, &_camera);
	WorldItems.init(&Lights, &spriteBatch);
	drawText.init(&spriteBatch);
	_camera.setScreenShakeIntensity(10);
	drones.init(&spriteBatch, &WorldItems, &_camera, &Lights, &projectiles);
	drones.add(0, 3200);
	drones.addTarget(player.getBoundingBox());
	walkers.init(&spriteBatch, &WorldItems, &_camera, &Lights, &projectiles);
	walkers.add(200, 3200);
	walkers.addTarget(player.getBoundingBox());
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
	player.handleInput(&_inputManager);
	WorldItems.runItems();
	drones.run();
	walkers.run();
	projectiles.run();
	_camera.followObject(player.getBoundingBox());
	for (int i = 0; i < projectiles.getVectorSize(); i++) {
		bool remove = false;
		if (projectiles.getToDelete(i))
		{
			projectiles.remove(i);
			i--;
		}
		else {
			if (projectiles.getProjectile(i)->getDamageType() == damageDrone) {
				for (int j = 0; j < drones.getVectorSize(); j++) {
					if (cd.lineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), drones.getBoundingBox(j))) {
						remove = true;
						//WorldItems.addItem(explosion, cd.getLineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), drones.getBoundingBox(j)));
						projectiles.getProjectile(i)->setPosition(cd.getLineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), drones.getBoundingBox(j)));
						drones.reduceHealth(j, 2);
					}
				}
				for (int j = 0; j < walkers.getVectorSize(); j++) {
					if (cd.lineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), walkers.getBoundingBox(j))) {
						remove = true;
						//WorldItems.addItem(explosion, cd.getLineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), drones.getBoundingBox(j)));
						projectiles.getProjectile(i)->setPosition(cd.getLineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), walkers.getBoundingBox(j)));
						walkers.reduceHealth(j, 2);
					}
				}
			} else if (projectiles.getProjectile(i)->getDamageType() == damagePlayer)
			{
				if (cd.doLinesColide(player.shield1, player.shield2, projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition()))
				{
					remove = true;
					projectiles.getProjectile(i)->setPosition(cd.getLineIntersect(player.shield1, player.shield2, projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition()));
				}
				if (cd.lineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), player.getBoundingBox())) {
					remove = true;
					projectiles.getProjectile(i)->setPosition(cd.getLineRectCollision(projectiles.getProjectile(i)->getPosition(), projectiles.getProjectile(i)->getLastPosition(), player.getBoundingBox()));
					player.reduceHealth(2);
				}
			}
			if (remove) {
				projectiles.setToDelete(i, true);
			}
		}
	}
	for (int j = 0; j < Platforms.getVectorSize(); j++)
	{
		cd.correctPosition(player.getBoundingBox(), Platforms.getBoundingBox(j));
		for (int i = 0; i < WorldItems.getVectorSize(); i++)
		{
			if (cd.isCheckRequired(WorldItems.getBoundingBox(i), Platforms.getBoundingBox(j)))
			{
				cd.correctPosition(WorldItems.getBoundingBox(i), Platforms.getBoundingBox(j));
			}
		}
		for (int i = 0; i < walkers.getVectorSize(); i++) {
			cd.correctPosition(walkers.getBoundingBox(i), Platforms.getBoundingBox(j));
		}
	}
	player.calcNewPos();
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
    }*/
    if (_inputManager.isKeyPressed(SDLK_y)) {
		player.getBoundingBox()->y = 3100;
		player.getBoundingBox()->x = -100;
		lightPos.x+=10;
    }
    if (_inputManager.isKeyPressed(SDLK_q)) {
        //_camera.setScale(_camera.getScale() + SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDLK_e)) {
        //_camera.setScale(_camera.getScale() - SCALE_SPEED);
    }
	if (_inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		if (!_inputManager.lastMouseR) {
			drones.add(mouseCoords.x, -mouseCoords.y);
		}
	}
	if (_inputManager.isKeyPressed(SDL_BUTTON_MIDDLE)) {
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = _camera.convertScreenToWorld(mouseCoords);
		if (!_inputManager.lastMouseM) {
			walkers.add(mouseCoords.x, -mouseCoords.y);
		}
	}
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
    spriteBatch.begin();
    glm::vec4 pos(-100.0f, -100.0f, 500.0f, 500.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	glm::vec4 pos1(-1000.0f, 1000.0f, 2000.0f, -2000.0f);
	glm::vec4 uv1(0.0f, 0.0f, 1.0f, 1.0f);
	//static GameEngine::GLTexture newTexture = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/b1.png");
	//static GameEngine::GLTexture newTexture1 = GameEngine::ResourceManager::getTexture("Textures/jimmyJump_pack/PNG/b2.png");
	static GameEngine::GLTexture db = GameEngine::ResourceManager::getTexture("Textures/decentBackground.png");
	static GameEngine::GLTexture mb = GameEngine::ResourceManager::getTexture("Textures/meshBackground.png");
	static GameEngine::GLTexture test = GameEngine::ResourceManager::getTexture("Textures/guardian.png");
    GameEngine::Color color;
    color.r = 255;
    color.g = 0;
    color.b = 255;
    color.a = 255;
	//_spriteBatch.draw(pos1, uv1, newTexture1.id, 0.0f, color, 0.5);
	//_spriteBatch.draw(pos1, uv1, newTexture.id, 0.0f, color, 1);
	
	spriteBatch.draw(glm::vec4(-6500 / 2, -6500 / 2, 6500, 6500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.8, 0.8, 0, 0), uv1, db.id, 0.0f, color, 0);
	//_spriteBatch.draw(glm::vec4(-9500 / 2, -5500 / 2, 9500, 5500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.6, 0.7, 0, 0), uv1, mb.id, 0.0f, color, 0.5);
	spriteBatch.draw(glm::vec4(-9500 / 2, -5500 / 2, 9500, 5500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.6, 0.6, 0, 0), uv1, mb.id, 0.0f, color, 0.3);
	spriteBatch.draw(glm::vec4(-9500 / 2, -5500 / 2, 9500, 5500) + glm::vec4(_camera.getPosition().x - _camera.getVelocity().x, _camera.getPosition().y - _camera.getVelocity().y, 0, 0)*glm::vec4(0.6, 0.6, 0, 0) + glm::vec4(3, 3, 0, 0), uv1, mb.id, 0.0f, color, 0.4);
	spriteBatch.draw(glm::vec4(0.0f, 3000.0f, 28 * 2, 67 * 2), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), test.id, 0.0f, color, 1);

    spriteBatch.draw(pos, uv, texture.id, 0.0f, color);
	GameEngine::drawRect(300, 0, 600, 600, 1, color, &spriteBatch);
	//_spriteBatch.drawLine(glm::vec2(0, 3200), glm::vec2(100, 3100), 255, 150, 0, 255);
	//_spriteBatch.drawLine(glm::vec2(0, 3200), glm::vec2(100, 3100), color);
	Platforms.drawPlatforms(&spriteBatch);
	player.draw();
	projectiles.draw();
	//drawText.draw(-30, 3100, "a", 1);
	WorldItems.drawItems();
	drones.draw();
	walkers.draw();
	if (_inputManager.isKeyPressed(SDLK_TAB)) {
		player.drawInventory(_camera.getPosition() - _camera.getVelocity());
	}
	spriteBatch.end();
	
    spriteBatch.renderBatch();

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