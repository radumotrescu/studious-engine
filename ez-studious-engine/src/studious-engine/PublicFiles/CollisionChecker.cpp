#include "CollisionChecker.h"

namespace SE {

	auto CollisionChecker::isCollided(IEntity * entity1, IEntity * entity2) -> bool
	{
		if ((entity1->getType() == Type::RECTANGLE) && (entity2->getType() == Type::RECTANGLE))
		{
			Rectangle* rect1 = dynamic_cast<Rectangle*>(entity1);
			Rectangle* rect2 = dynamic_cast<Rectangle*>(entity2);
			return isCollided(*rect1, *rect2);
		}
		return false;
	}

	auto CollisionChecker::isCollided(Rectangle rect1, Rectangle rect2) -> bool
	{
		auto minRange1X = rect1.getOrigin().x;
		auto maxRange1X = rect1.getOrigin().x + rect1.getWidth();
		auto minRange2X = rect2.getOrigin().x;
		auto maxRange2X = rect2.getOrigin().x + rect2.getWidth();

		auto minRange1Y = rect1.getOrigin().y;
		auto maxRange1Y = rect1.getOrigin().y + rect1.getHeight();
		auto minRange2Y = rect2.getOrigin().y;
		auto maxRange2Y = rect2.getOrigin().y + rect2.getHeight();
		return Utils::rangeIntersection(minRange1X, maxRange1X, minRange2X, maxRange2X) &&
			Utils::rangeIntersection(minRange1Y, maxRange1Y, minRange2Y, maxRange2Y);
	}

	auto CollisionChecker::isCollided(vec3 point, Rectangle rect) -> bool
	{
		auto minRangeX = rect.getOrigin().x;
		auto maxRangeX = rect.getOrigin().x + rect.getWidth();
		auto minRangeY = rect.getOrigin().y;
		auto maxRangeY = rect.getOrigin().y + rect.getHeight();
		return Utils::inRange(point.x, minRangeX, maxRangeX) && Utils::inRange(point.y, minRangeY, maxRangeY);
	}

	auto CollisionChecker::determinant(float a, float b, float c, float d)->float
	{
		return a*d - b*c;
	}

	auto CollisionChecker::lineIntersection(vec3 point1, vec3 point2, vec3 point3, vec3 point4, vec3& intersectionPoint)->bool
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
}
