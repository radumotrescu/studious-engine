#pragma once

#include <algorithm>
#include <limits>
#include "Entity.h"
//#include "Triangle.h"
#include "Rectangle.h"

class Application
{
public:
	Application() {};
	//Application() = default;
	~Application() = default;

	auto isCollided(IEntity* entity1, IEntity* entity2)->bool;

private:
	auto approximatelyEqual(float a, float b, float epsilon = EPSILON)->bool;
	auto essentiallyEqual(float a, float b, float epsilon = EPSILON)->bool;
	auto definitelyGreaterThan(float a, float b, float epsilon = EPSILON)->bool;
	auto definitelyLessThan(float a, float b, float epsilon = EPSILON)->bool;
	auto rangeIntersection(float minRange1, float maxRange1, float minRange2, float maxRange2)->bool;
	auto inRange(float value, float minRange, float maxRange)->bool;
	auto determinant(float a, float b, float c, float d)->float;
	auto lineIntersection(vec3 point1, vec3 point2, vec3 point3, vec3 point4, vec3& intersectionPoint)->bool;

	auto isCollided(stud::Rectangle rect1, stud::Rectangle rect2)->bool;
	auto isCollided(vec3 point, stud:: Rectangle rect)->bool;
	//auto isCollided(Triangle triangle1, Triangle triangle2)->bool;
	//auto isCollided(Point3D point, Triangle triangle)->bool;
	//auto isCollided(Rectangle rect, Triangle triangle)->bool;

private:
	static const float EPSILON;
};

