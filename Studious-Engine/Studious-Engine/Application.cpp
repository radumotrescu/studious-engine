#include "Application.h"

const float Application::EPSILON = std::numeric_limits<float>::epsilon();

auto Application::isCollided(IEntity * a, IEntity * b) -> bool
{
	//Point3D missing from the IEntity hierarchy
	if (a->getType() == Type::RECTANGLE && b->getType() == Type::RECTANGLE)
	{
		Rectangle* rect1 = dynamic_cast<Rectangle*>(a);
		Rectangle* rect2 = dynamic_cast<Rectangle*>(b);
		return isCollided(rect1, rect2);
	}
	else if (a->getType() == Type::RECTANGLE && b->getType() == Type::TRIANGLE)
	{
		Rectangle* rectangle = dynamic_cast<Rectangle*>(a);
		Triangle* triangle = dynamic_cast<Triangle*>(b);
		return isCollided(rectangle, triangle);
	}
	else  if (a->getType() == Type::TRIANGLE && b->getType() == Type::RECTANGLE)
	{
		Rectangle* rectangle = dynamic_cast<Rectangle*>(b);
		Triangle* triangle = dynamic_cast<Triangle*>(a);
		return isCollided(rectangle, triangle);
	}
	else if (a->getType() == Type::TRIANGLE && b->getType() == Type::TRIANGLE)
	{
		Triangle* triangle1 = dynamic_cast<Triangle*>(a);
		Triangle* triangle2 = dynamic_cast<Triangle*>(b);
		return isCollided(triangle1, triangle2);
	}

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
	auto greaterOrEqual = essentiallyEqual((std::max)(minRange1, maxRange1), (std::min)(minRange1, maxRange1)) || definitelyGreaterThan((std::max)(minRange1, maxRange1), (std::min)(minRange1, maxRange1));
	auto lessOrEqual = essentiallyEqual((std::max)(minRange1, maxRange1), (std::min)(minRange1, maxRange1)) || definitelyGreaterThan((std::min)(minRange1, maxRange1), (std::max)(minRange1, maxRange1));

	return  lessOrEqual && greaterOrEqual;
}

auto Application::inRange(float value, float minRange, float maxRange) -> bool
{
	auto greaterOrEqual = essentiallyEqual((std::min)(minRange, maxRange), value) || definitelyGreaterThan((std::min)(minRange, maxRange), value);
	auto lessOrEqual = essentiallyEqual((std::min)(minRange, maxRange), value) || definitelyGreaterThan(value, (std::min)(minRange, maxRange));

	return lessOrEqual && greaterOrEqual;
}

auto Application::isCollided(Rectangle rect1, Rectangle rect2) -> bool
{
	auto minRange1X = rect1.getPoints().at(0).x;
	auto maxRange1X = rect1.getPoints().at(0).x + rect1.getWidth();
	auto minRange2X = rect2.getPoints().at(0).x;
	auto maxRange2X = rect2.getPoints().at(0).x + rect2.getWidth();

	auto minRange1Y = rect1.getPoints().at(0).y;
	auto maxRange1Y = rect1.getPoints().at(0).y + rect1.getHeight();
	auto minRange2Y = rect2.getPoints().at(0).y;
	auto maxRange2Y = rect2.getPoints().at(0).y + rect2.getHeight();
	return rangeIntersection(minRange1X, maxRange1X, minRange2X, maxRange2X) &&
		rangeIntersection(minRange1Y, maxRange1Y, minRange2Y, maxRange2Y);
}

auto Application::isCollided(Point3D point, Rectangle rect) -> bool
{
	auto minRangeX = rect.getPoints().at(0).x;
	auto maxRangeX = rect.getPoints().at(0).x + rect.getWidth();
	auto minRangeY = rect.getPoints().at(0).y;
	auto maxRangeY = rect.getPoints().at(0).y + rect.getHeight();
	return inRange(point.x, minRangeX, maxRangeX) && inRange(point.y, minRangeY, maxRangeY);
}

auto Application::isCollided(Triangle triangle1, Triangle triangle2) -> bool
{
	auto A2collidedToTriangle1 = isCollided(triangle2.getPoints().at(0), triangle1);
	auto B2collidedToTriangle1 = isCollided(triangle2.getPoints().at(1), triangle1);
	auto C2collidedToTriangle1 = isCollided(triangle2.getPoints().at(2), triangle1);
	return A2collidedToTriangle1 || B2collidedToTriangle1 || C2collidedToTriangle1;
}

auto Application::isCollided(Point3D point, Triangle triangle) -> bool
{
	auto aX = triangle.getPoints().at(0).x;
	auto aY = triangle.getPoints().at(0).y;
	auto bX = triangle.getPoints().at(1).x;
	auto bY = triangle.getPoints().at(1).y;
	auto cX = triangle.getPoints().at(2).x;
	auto cY = triangle.getPoints().at(2).y;

	auto triangleArea = (aX * (bY - cY) + bX * (cY - aY) + cX * (aY - bY)) / 2;

	auto segment1Area = (aX * (bY - point.y) + bX * (point.y - aY) + point.x * (aY - bY)) / 2; // A B A2

	auto segment2Area = (aX * (point.y - cY) + point.x * (cY - aY) + cX * (aY - point.y)) / 2; // A A2 C

	auto segment3Area = (point.x * (bY - cY) + bX * (cY - point.y) + cX * (point.y - bY)) / 2; // A2 B C

	return	essentiallyEqual(triangleArea, segment1Area + segment2Area + segment3Area);
}

auto Application::isCollided(Rectangle rect, Triangle triangle) -> bool
{
	auto A = triangle.getPoints().at(0);
	auto B = triangle.getPoints().at(1);
	auto C = triangle.getPoints().at(2);

	auto A1 = rect.getPoints().at(0);
	auto B1 = rect.getPoints().at(1);
	auto C1 = rect.getPoints().at(2);
	auto D1 = rect.getPoints().at(3);

	Point3D intersectionPoint;

	auto ABtoA1D1 = lineIntersection(A, B, A1, D1, intersectionPoint);
	auto BCtoA1D1 = lineIntersection(B, C, A1, D1, intersectionPoint);
	auto ACtoA1D1 = lineIntersection(A, C, A1, D1, intersectionPoint);

	auto ABtoA1B1 = lineIntersection(A, B, A1, B1, intersectionPoint);
	auto BCtoA1B1 = lineIntersection(B, C, A1, B1, intersectionPoint);
	auto ACtoA1B1 = lineIntersection(A, C, A1, B1, intersectionPoint);

	auto ABtoB1C1 = lineIntersection(A, B, B1, C1, intersectionPoint);
	auto BCtoB1C1 = lineIntersection(B, C, B1, C1, intersectionPoint);
	auto ACtoB1C1 = lineIntersection(A, C, B1, C1, intersectionPoint);

	auto ABtoD1C1 = lineIntersection(A, B, D1, C1, intersectionPoint);
	auto BCtoD1C1 = lineIntersection(B, C, D1, C1, intersectionPoint);
	auto ACtoD1C1 = lineIntersection(A, C, D1, C1, intersectionPoint);

	return ABtoA1D1 || BCtoA1D1 || ACtoA1D1 ||
		ABtoA1B1 || BCtoA1B1 || ACtoA1B1 ||
		ABtoB1C1 || BCtoB1C1 || ACtoB1C1 ||
		ABtoD1C1 || BCtoD1C1 || ACtoD1C1;
}

auto Application::determinant(float a, float b, float c, float d)->float
{
	return a*d - b*c;
}

auto Application::lineIntersection(Point3D point1, Point3D point2, Point3D point3, Point3D point4, Point3D& intersectionPoint)->bool
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