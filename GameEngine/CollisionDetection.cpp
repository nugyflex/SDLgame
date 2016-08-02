#include  "CollisionDetection.h"
#include <iostream>

namespace GameEngine {
	CollisionDetection::CollisionDetection() {}
	CollisionDetection::~CollisionDetection() {}
	bool CollisionDetection::CheckRectangleIntersect(glm::vec4* _rect1, glm::vec4* _rect2)
	{
		if (_rect1->x + _rect1->z > _rect2->x && _rect1->x < _rect2->x + _rect2->z && _rect1->y + _rect1->w > _rect2->y && _rect1->y < _rect2->y + _rect2->w)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool CollisionDetection::test1(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->x + _rect1->z >= _rect2->x) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test2(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->x >= _rect2->x) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test3(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->x >= _rect2->x + _rect2->z) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test4(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->x + _rect1->z >= _rect2->x + _rect2->z) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test5(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->y >= _rect2->y) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test6(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->y + _rect1->w >= _rect2->y) {
			return true;
		}
		return false;
	}

	bool CollisionDetection::test7(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->y + _rect1->w >= _rect2->y + _rect2->w) {
			return true;
		}
		return false;
	}
	bool CollisionDetection::test8(glm::vec4* _rect1, glm::vec4* _rect2) {
		if (_rect1->y >= _rect2->y + _rect2->w) {
			return true;
		}
		return false;
	}

	int CollisionDetection::getSide(glm::vec4* _rect1, glm::vec4* _rect2) {
		int result = -1;
		int testvar = 0;
		if (test1(_rect1, _rect2))
		{
			testvar = testvar + 1;
		}
		if (test2(_rect1, _rect2)) {
			testvar = testvar + 2;
		}
		if (test3(_rect1, _rect2)) {
			testvar = testvar + 4;
		}
		if (test4(_rect1, _rect2)) {
			testvar = testvar + 8;
		}
		if (test5(_rect1, _rect2)) {
			testvar = testvar + 16;
		}
		if (test6(_rect1, _rect2)) {
			testvar = testvar + 32;
		}
		if (test7(_rect1, _rect2)) {
			testvar = testvar + 64;
		}
		if (test8(_rect1, _rect2)) {
			testvar = testvar + 128;
		}
		switch (testvar)
		{
			//left = 1, bottom = 2, right = 3, top = 4
			// 0,1,1,1,1,0,0,1=121
		case 121:
			result = 2;
			break;
			//0,0,1,0,1,0,0,1=73
		case 73:
			result = 4;
			break;
			//0,1,1,0,1,0,1,1
		case 107:
			result = 3;
			break;
			//0,1,1,0,0,0,0,1
		case 97:
			result = 1;
			break;
			//0,0,1,0,0,0,1,1
		case 35:
			result = 4;
			break;
			//0,0,1,1,0,0,0,1
		case 49:
			result = 1;
			break;
			//0,0,1,1,1,0,1,1 = 59
		case 59:
			result = 3;
			break;
			//0,1,1,1,0,0,1,1 = 115
		case 115:
			result = 2;
			break;
			//top left corner
			//0,0,1,0,0,0,0,1
		case 33:
			if ((_rect1->x + _rect1->z) - _rect2->x > (_rect1->y + _rect1->w) - _rect2->y) {
				result = 4;
			}
			else {
				result = 1;
			}
			break;

			//top right corner
			//0,0,1,0,1,0,1,1 = 43
		case 43:
			if (_rect2->x + _rect2->z - _rect1->x > (_rect1->y + _rect1->w) - _rect2->y) {
				result = 4;
			}
			else {
				result = 3;
			}
			break;

			//bottom left corner
			//0,1,1,1,0,0,0,1 = 113
		case 113:
			if (_rect1->x + _rect1->z - _rect2->x > _rect2->y + _rect2->w - _rect1->y) {
				result = 2;
			}
			else
			{
				result = 1;
			}
			break;

			//bottom right corner
			//0,1,1,1,1,0,1,1 = 123
		case 123:
			if (_rect2->x + _rect2->z - _rect1->x > _rect2->y + _rect2->w - _rect1->y) {
				result = 2;
			}
			else {
				result = 3;
			}
			break;
		}

		return result;
	}
	//this function corrects the position of a rectangle if it is colliding with another rectangle
	void CollisionDetection::correctPosition(glm::vec4* _rect1, glm::vec4* _rect2) {
		//left = 1, bottom = 2, right = 3, top = 4
		if (CheckRectangleIntersect(_rect1, _rect2))
		{
			switch (getSide(_rect1, _rect2))
			{
			case 1:
				_rect1->x = _rect2->x - _rect1->z;
				break;
			case 3:
				_rect1->x = (_rect2->x + _rect2->z);
				break;
			case 2:
				_rect1->y = (_rect2->y + _rect2->w);
				break;
			case 4:
				_rect1->y = (_rect2->y - _rect1->w);
				break;
			}
		}
	}
	void CollisionDetection::correctPosition(glm::vec4* _rect1, glm::vec4* _rect2, glm::vec2 *_vel) {
		//left = 1, bottom = 2, right = 3, top = 
		if (CheckRectangleIntersect(_rect1, _rect2))
		{
			switch (getSide(_rect1, _rect2))
			{
			case 1:
				if (_vel->x > 0) { _vel->x = 0; }
				_rect1->x = _rect2->x - _rect1->z;
				break;
			case 3:
				if (_vel->x < 0) { _vel->x = 0; }
				_rect1->x = (_rect2->x + _rect2->z);
				break;
			case 2:
				std::cout << "yVEL: " << _vel->y << std::endl;
				if (_vel->y < 0) { _vel->y = 0; }
				_rect1->y = (_rect2->y + _rect2->w);
				std::cout << "yVEL: " << _vel->y << std::endl;
				break;
			case 4:
				if (_vel->y < 0) { _vel->y = 0; }
				_rect1->y = (_rect2->y - _rect1->w);
				break;
			}
			*_vel = glm::vec2(_vel->x, _vel->y);
		}
	}
}