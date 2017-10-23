#pragma once

#include <algorithm>
#include <limits>
#include "IEntity.h"
//#include "Triangle.h"
#include "Rectangle.h"

#include "Utils.h"


namespace SE {

	class CollisionChecker {
	public:
		//Application() {};
		CollisionChecker() = default;
		~CollisionChecker() = default;

		auto isCollided(IEntity* entity1, IEntity* entity2)->bool;

	private:

		auto determinant(float a, float b, float c, float d)->float;
		auto lineIntersection(vec3 point1, vec3 point2, vec3 point3, vec3 point4, vec3& intersectionPoint)->bool;

		auto isCollided(Rectangle rect1, SE::Rectangle rect2)->bool;
		auto isCollided(vec3 point, SE::Rectangle rect)->bool;

	};
}
