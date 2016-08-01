#pragma once
#include "Math.h"
#include <vector>
#include <glm.hpp>
namespace GameEngine {
	class CollisionDetection
	{
	public:
		CollisionDetection();
		~CollisionDetection();
		bool CheckRectangleIntersect(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test1(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test2(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test3(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test4(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test5(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test6(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test7(glm::vec4* _rect1, glm::vec4* _rect2);
		bool test8(glm::vec4* _rect1, glm::vec4* _rect2);
		int getSide(glm::vec4* _rect1, glm::vec4* _rect2);
		void correctPosition(glm::vec4* _rect1, glm::vec4* _rect2);
		void correctPosition(glm::vec4* _rect1, glm::vec4* _rect2, glm::vec2* _vel);
	};
}