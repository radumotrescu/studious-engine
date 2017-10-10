#include "Application.h"

const float Application::EPSILON = std::numeric_limits<float>::epsilon();

auto Application::isCollided(IEntity * entity1, IEntity * entity2) -> bool
{
	//Point3D missing from the IEntity hierarchy
	if ((entity1->getType() == Type::RECTANGLE) && (entity2->getType() == Type::RECTANGLE))
	{
		stud::Rectangle* rect1 = dynamic_cast<stud::Rectangle*>(entity1);
		stud::Rectangle* rect2 = dynamic_cast<stud::Rectangle*>(entity2);
		return isCollided(*rect1, *rect2);
	}
	//else if (entity1->getType() == Type::RECTANGLE && entity2->getType() == Type::TRIANGLE)
	//{
	//	Rectangle* rectangle = dynamic_cast<Rectangle*>(entity1);
	//	Triangle* triangle = dynamic_cast<Triangle*>(entity2);
	//	return isCollided(rectangle, triangle);
	//}
	//else  if (entity1->getType() == Type::TRIANGLE && entity2->getType() == Type::RECTANGLE)
	//{
	//	Rectangle* rectangle = dynamic_cast<Rectangle*>(entity2);
	//	Triangle* triangle = dynamic_cast<Triangle*>(entity1);
	//	return isCollided(rectangle, triangle);
	//}
	//else if (entity1->getType() == Type::TRIANGLE && entity2->getType() == Type::TRIANGLE)
	//{
	//	Triangle* triangle1 = dynamic_cast<Triangle*>(entity1);
	//	Triangle* triangle2 = dynamic_cast<Triangle*>(entity2);
	//	return isCollided(triangle1, triangle2);
	//}

	return false;
}

auto Application::approximatelyEqual(float a, float b, float epsilon)->bool
{
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto Application::essentiallyEqual(float a, float b, float epsilon)->bool
{
	return fabs(a - b) <= ((fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto Application::definitelyGreaterThan(float a, float b, float epsilon)->bool
{
	return (a - b) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto Application::definitelyLessThan(float a, float b, float epsilon)->bool
{
	return (b - a) > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

auto Application::rangeIntersection(float minRange1, float maxRange1, float minRange2, float maxRange2) -> bool
{
	auto min1 = (std::min)(minRange1, maxRange1);
	auto min2 = (std::min)(minRange2, maxRange2);
	auto max1 = (std::max)(minRange1, maxRange1);
	auto max2 = (std::max)(minRange2, maxRange2);

	auto minLessOrEqualToValue1 = essentiallyEqual(min1, min2) || definitelyLessThan(min1, min2);
	auto value1LessOrEqualToMax = essentiallyEqual(min2, max1) || definitelyLessThan(min2, max1);

	auto minLessOrEqualToValue2 = essentiallyEqual(min1, max2) || definitelyLessThan(min1, max2);
	auto value2LessOrEqualToMax = essentiallyEqual(max2, max1) || definitelyLessThan(max2, max1);

	return  (minLessOrEqualToValue1 && value1LessOrEqualToMax) || (minLessOrEqualToValue2 && value2LessOrEqualToMax);
}

auto Application::inRange(float value, float minRange, float maxRange) -> bool
{
	auto greaterOrEqual = essentiallyEqual((std::min)(minRange, maxRange), value) || definitelyGreaterThan((std::min)(minRange, maxRange), value);
	auto lessOrEqual = essentiallyEqual((std::min)(minRange, maxRange), value) || definitelyGreaterThan(value, (std::min)(minRange, maxRange));

	return lessOrEqual && greaterOrEqual;
}

auto Application::isCollided(stud::Rectangle rect1, stud::Rectangle rect2) -> bool
{
	auto minRange1X = rect1.getOrigin().x;
	auto maxRange1X = rect1.getOrigin().x + rect1.getWidth();
	auto minRange2X = rect2.getOrigin().x;
	auto maxRange2X = rect2.getOrigin().x + rect2.getWidth();

	auto minRange1Y = rect1.getOrigin().y;
	auto maxRange1Y = rect1.getOrigin().y + rect1.getHeight();
	auto minRange2Y = rect2.getOrigin().y;
	auto maxRange2Y = rect2.getOrigin().y + rect2.getHeight();
	return rangeIntersection(minRange1X, maxRange1X, minRange2X, maxRange2X) &&
		rangeIntersection(minRange1Y, maxRange1Y, minRange2Y, maxRange2Y);
}

auto Application::isCollided(vec3 point, stud::Rectangle rect) -> bool
{
	auto minRangeX = rect.getOrigin().x;
	auto maxRangeX = rect.getOrigin().x + rect.getWidth();
	auto minRangeY = rect.getOrigin().y;
	auto maxRangeY = rect.getOrigin().y + rect.getHeight();
	return inRange(point.x, minRangeX, maxRangeX) && inRange(point.y, minRangeY, maxRangeY);
}

//auto Application::isCollided(Triangle triangle1, Triangle triangle2) -> bool
//{
//	auto A2collidedToTriangle1 = isCollided(triangle2.getPoints().at(0), triangle1);
//	auto B2collidedToTriangle1 = isCollided(triangle2.getPoints().at(1), triangle1);
//	auto C2collidedToTriangle1 = isCollided(triangle2.getPoints().at(2), triangle1);
//	return A2collidedToTriangle1 || B2collidedToTriangle1 || C2collidedToTriangle1;
//}
//
//auto Application::isCollided(Point3D point, Triangle triangle) -> bool
//{
//	auto aX = triangle.getPoints().at(0).x;
//	auto aY = triangle.getPoints().at(0).y;
//	auto bX = triangle.getPoints().at(1).x;
//	auto bY = triangle.getPoints().at(1).y;
//	auto cX = triangle.getPoints().at(2).x;
//	auto cY = triangle.getPoints().at(2).y;
//
//	auto triangleArea = (aX * (bY - cY) + bX * (cY - aY) + cX * (aY - bY)) / 2;
//
//	auto segment1Area = (aX * (bY - point.y) + bX * (point.y - aY) + point.x * (aY - bY)) / 2; // A B A2
//
//	auto segment2Area = (aX * (point.y - cY) + point.x * (cY - aY) + cX * (aY - point.y)) / 2; // A A2 C
//
//	auto segment3Area = (point.x * (bY - cY) + bX * (cY - point.y) + cX * (point.y - bY)) / 2; // A2 B C
//
//	return	essentiallyEqual(triangleArea, segment1Area + segment2Area + segment3Area);
//}
//
//auto Application::isCollided(Rectangle rect, Triangle triangle) -> bool
//{
//	auto A = triangle.getPoints().at(0);
//	auto B = triangle.getPoints().at(1);
//	auto C = triangle.getPoints().at(2);
//
//	auto A1 = rect.getPoints().at(0);
//	auto B1 = rect.getPoints().at(1);
//	auto C1 = rect.getPoints().at(2);
//	auto D1 = rect.getPoints().at(3);
//
//	Point3D intersectionPoint;
//
//	auto ABtoA1D1 = lineIntersection(A, B, A1, D1, intersectionPoint);
//	auto BCtoA1D1 = lineIntersection(B, C, A1, D1, intersectionPoint);
//	auto ACtoA1D1 = lineIntersection(A, C, A1, D1, intersectionPoint);
//
//	auto ABtoA1B1 = lineIntersection(A, B, A1, B1, intersectionPoint);
//	auto BCtoA1B1 = lineIntersection(B, C, A1, B1, intersectionPoint);
//	auto ACtoA1B1 = lineIntersection(A, C, A1, B1, intersectionPoint);
//
//	auto ABtoB1C1 = lineIntersection(A, B, B1, C1, intersectionPoint);
//	auto BCtoB1C1 = lineIntersection(B, C, B1, C1, intersectionPoint);
//	auto ACtoB1C1 = lineIntersection(A, C, B1, C1, intersectionPoint);
//
//	auto ABtoD1C1 = lineIntersection(A, B, D1, C1, intersectionPoint);
//	auto BCtoD1C1 = lineIntersection(B, C, D1, C1, intersectionPoint);
//	auto ACtoD1C1 = lineIntersection(A, C, D1, C1, intersectionPoint);
//
//	return ABtoA1D1 || BCtoA1D1 || ACtoA1D1 ||
//		ABtoA1B1 || BCtoA1B1 || ACtoA1B1 ||
//		ABtoB1C1 || BCtoB1C1 || ACtoB1C1 ||
//		ABtoD1C1 || BCtoD1C1 || ACtoD1C1;
//}

auto Application::determinant(float a, float b, float c, float d)->float
{
	return a*d - b*c;
}

auto Application::lineIntersection(vec3 point1, vec3 point2, vec3 point3, vec3 point4, vec3& intersectionPoint)->bool
{


	auto detL1 = determinant(point1.x, point1.y, point2.x, point2.y);
	auto detL2 = determinant(point3.x, point3.y, point4.x, point4.y);
	auto x1mx2 = point1.x - point2.x;
	auto x3mx4 = point3.x - point4.x;
	auto y1my2 = point1.y - point2.y;
	auto y3my4 = point3.y - point4.y;

	auto xnom = determinant(detL1, x1mx2, detL2, x3mx4);
	auto ynom = determinant(detL1, y1my2, detL2, y3my4);
	auto denom = determinant(x1mx2, y1my2, x3mx4, y3my4);
	if (denom == 0.0)
	{
		intersectionPoint.x = NAN;
		intersectionPoint.y = NAN;
		return false;
	}

	intersectionPoint.x = xnom / denom;
	intersectionPoint.y = ynom / denom;
	if (!isfinite(intersectionPoint.x) || !isfinite(intersectionPoint.y))
		return false;

	return true;
}