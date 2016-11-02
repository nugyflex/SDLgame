#include <SDL.h>
#include <GL/glew.h>
#include "GameEngine.h"

namespace GameEngine {
	int init() {
		//Initialize SDL
		SDL_Init(SDL_INIT_EVERYTHING);

		//Tell SDL that we want a double buffered window so we dont get
		//any flickering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);
		return 0;
	}
	void drawRect(int x, int y, int width, int height, float _lightAlpha, Color color, SpriteBatch* spriteBatch) {
		spriteBatch->draw(glm::vec4(x, y, width, height), glm::vec4(1, 1, 1, 1), NULL, 0.0f, color, _lightAlpha);
	}
	void drawLine(glm::vec2 point1, glm::vec2 point2, glm::mat4 cameraMatrix) {
		glBegin(GL_LINES);
		glm::vec4 test1 = cameraMatrix * glm::vec4(point1.x, point1.y, 1, 1);
		glVertex3f(test1.x, test1.y, 0);
		glm::vec4 test = cameraMatrix * glm::vec4(point2.x, point2.y, 1, 1);
		glVertex3f(test.x, test.y, 0);
		glEnd();
	}
	void drawBasicLine(glm::vec2 _point1, glm::vec2 _point2, float _thickness, float _r, float _g, float _b) {
		glLineWidth(_thickness);
		glColor3f(_r, _g, _b);
		glBegin(GL_LINES);
		glVertex3f(_point1.x, _point1.y, 0.0);
		glVertex3f(_point2.x, _point2.y, 0.0);
		glEnd();
	}
	void fillBackGround(float _r, float _g, float _b) {
		glColor3f(_r, _g, _b);
		glBegin(GL_POLYGON);
		glVertex3f(-1, -1, 0.0);
		glVertex3f(1, -1, 0.0);
		glVertex3f(1, 1, 0.0);
		glVertex3f(-1, 1, 0.0);
		glEnd();
	}
}